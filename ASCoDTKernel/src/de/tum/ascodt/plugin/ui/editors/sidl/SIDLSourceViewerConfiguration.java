package de.tum.ascodt.plugin.ui.editors.sidl;


import org.eclipse.jface.text.DefaultIndentLineAutoEditStrategy;
import org.eclipse.jface.text.IAutoEditStrategy;
import org.eclipse.jface.text.IDocument;
import org.eclipse.jface.text.ITextDoubleClickStrategy;
import org.eclipse.jface.text.ITextHover;
import org.eclipse.jface.text.TextAttribute;
import org.eclipse.jface.text.contentassist.ContentAssistant;
import org.eclipse.jface.text.contentassist.IContentAssistant;
import org.eclipse.jface.text.presentation.IPresentationReconciler;
import org.eclipse.jface.text.presentation.PresentationReconciler;
import org.eclipse.jface.text.rules.BufferedRuleBasedScanner;
import org.eclipse.jface.text.rules.DefaultDamagerRepairer;
import org.eclipse.jface.text.rules.Token;
import org.eclipse.jface.text.source.IAnnotationHover;
import org.eclipse.jface.text.source.ISourceViewer;
import org.eclipse.jface.text.source.SourceViewerConfiguration;
import org.eclipse.swt.graphics.RGB;


public class SIDLSourceViewerConfiguration extends SourceViewerConfiguration {

  /**
   * Single token scanner.
   */
  static class SingleTokenScanner extends BufferedRuleBasedScanner {
    public SingleTokenScanner(TextAttribute attribute) {
      setDefaultReturnToken(new Token(attribute));
    }
  }

  /**
   * Default constructor.
   */
  public SIDLSourceViewerConfiguration() {}

  /*
   * (non-Javadoc)
   * Method declared on SourceViewerConfiguration
   */
  @Override
  public IAnnotationHover getAnnotationHover(ISourceViewer sourceViewer) {
    return new SIDLAnnotationHover();
  }

  /*
   * @see
   * org.eclipse.jface.text.source.SourceViewerConfiguration#getAutoEditStrategies
   * (org.eclipse.jface.text.source.ISourceViewer, java.lang.String)
   */
  @Override
  public IAutoEditStrategy[] getAutoEditStrategies(ISourceViewer sourceViewer,
                                                   String contentType) {
    IAutoEditStrategy strategy =
        IDocument.DEFAULT_CONTENT_TYPE.equals(contentType)
                                                          ? new SIDLAutoIndentStrategy()
                                                          : new DefaultIndentLineAutoEditStrategy();
    return new IAutoEditStrategy[] {strategy};
  }

  /*
   * (non-Javadoc)
   * Method declared on SourceViewerConfiguration
   */
  @Override
  public String[] getConfiguredContentTypes(ISourceViewer sourceViewer) {
    return new String[] {IDocument.DEFAULT_CONTENT_TYPE,
                         SIDLPartitionScanner.SIDL_DOC,
                         SIDLPartitionScanner.SIDL_MULTILINE_COMMENT};
  }

  /*
   * @see org.eclipse.jface.text.source.SourceViewerConfiguration#
   * getConfiguredDocumentPartitioning
   * (org.eclipse.jface.text.source.ISourceViewer)
   */
  @Override
  public String getConfiguredDocumentPartitioning(ISourceViewer sourceViewer) {
    return SIDLEditor.SIDL_PARTITIONING;
  }

  /*
   * (non-Javadoc)
   * Method declared on SourceViewerConfiguration
   */
  @Override
  public IContentAssistant getContentAssistant(ISourceViewer sourceViewer) {

    ContentAssistant assistant = new ContentAssistant();
    assistant.setDocumentPartitioning(getConfiguredDocumentPartitioning(sourceViewer));
    assistant.setContentAssistProcessor(new SIDLCompletionProcessor(),
                                        IDocument.DEFAULT_CONTENT_TYPE);
    // assistant.setContentAssistProcessor(new JavaDocCompletionProcessor(),
    // JavaPartitionScanner.JAVA_DOC);

    assistant.enableAutoActivation(true);
    assistant.setAutoActivationDelay(500);
    assistant.setProposalPopupOrientation(IContentAssistant.PROPOSAL_OVERLAY);
    assistant.setContextInformationPopupOrientation(IContentAssistant.CONTEXT_INFO_ABOVE);
    assistant.setContextInformationPopupBackground(SIDLEditor.getDefault()
                                                             .getSIDLColorProvider()
                                                             .getColor(new RGB(150,
                                                                               150,
                                                                               0)));

    return assistant;
  }

  /*
   * (non-Javadoc)
   * Method declared on SourceViewerConfiguration
   */
  @Override
  public ITextDoubleClickStrategy getDoubleClickStrategy(ISourceViewer sourceViewer,
                                                         String contentType) {
    return new SIDLDoubleClickSelector();
  }

  /*
   * (non-Javadoc)
   * Method declared on SourceViewerConfiguration
   */
  @Override
  public String[] getIndentPrefixes(ISourceViewer sourceViewer,
                                    String contentType) {
    return new String[] {"\t", "    "}; //$NON-NLS-1$ //$NON-NLS-2$
  }

  /*
   * (non-Javadoc)
   * Method declared on SourceViewerConfiguration
   */
  @Override
  public IPresentationReconciler getPresentationReconciler(ISourceViewer sourceViewer) {

    SIDLColorProvider provider = SIDLEditor.getDefault().getSIDLColorProvider();
    PresentationReconciler reconciler = new PresentationReconciler();
    reconciler.setDocumentPartitioning(getConfiguredDocumentPartitioning(sourceViewer));

    DefaultDamagerRepairer dr =
        new DefaultDamagerRepairer(SIDLEditor.getDefault().getSIDLCodeScanner());
    reconciler.setDamager(dr, IDocument.DEFAULT_CONTENT_TYPE);
    reconciler.setRepairer(dr, IDocument.DEFAULT_CONTENT_TYPE);

    dr =
        new DefaultDamagerRepairer(SIDLEditor.getDefault().getSIDLDocScanner());
    reconciler.setDamager(dr, SIDLPartitionScanner.SIDL_DOC);
    reconciler.setRepairer(dr, SIDLPartitionScanner.SIDL_DOC);

    dr =
        new DefaultDamagerRepairer(new SingleTokenScanner(new TextAttribute(provider.getColor(SIDLColorProvider.MULTI_LINE_COMMENT))));
    reconciler.setDamager(dr, SIDLPartitionScanner.SIDL_MULTILINE_COMMENT);
    reconciler.setRepairer(dr, SIDLPartitionScanner.SIDL_MULTILINE_COMMENT);

    return reconciler;
  }

  /*
   * (non-Javadoc)
   * Method declared on SourceViewerConfiguration
   */
  @Override
  public int getTabWidth(ISourceViewer sourceViewer) {
    return 4;
  }

  /*
   * (non-Javadoc)
   * Method declared on SourceViewerConfiguration
   */
  @Override
  public ITextHover getTextHover(ISourceViewer sourceViewer, String contentType) {
    return new SIDLTextHover();
  }
}
