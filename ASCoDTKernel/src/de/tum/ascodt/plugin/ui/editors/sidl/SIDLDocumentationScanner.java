package de.tum.ascodt.plugin.ui.editors.sidl;


import java.util.ArrayList;
import java.util.List;

import org.eclipse.jface.text.TextAttribute;
import org.eclipse.jface.text.rules.IRule;
import org.eclipse.jface.text.rules.IToken;
import org.eclipse.jface.text.rules.IWordDetector;
import org.eclipse.jface.text.rules.RuleBasedScanner;
import org.eclipse.jface.text.rules.SingleLineRule;
import org.eclipse.jface.text.rules.Token;
import org.eclipse.jface.text.rules.WhitespaceRule;
import org.eclipse.jface.text.rules.WordRule;


public class SIDLDocumentationScanner extends RuleBasedScanner {

  /**
   * A key word detector.
   */
  static class SIDLDocWordDetector implements IWordDetector {

    /*
     * (non-Javadoc)
     * Method declared on IWordDetector
     */
    @Override
    public boolean isWordPart(char c) {
      return Character.isLetter(c);
    }

    /*
     * (non-Javadoc)
     * Method declared on IWordDetector
     */
    @Override
    public boolean isWordStart(char c) {
      return c == '@';
    }
  }

  private static String[] fgKeywords = {
    "@author", "@deprecated", "@exception", "@param", "@return", "@see", "@serial", "@serialData", "@serialField", "@since", "@throws", "@version"}; //$NON-NLS-12$ //$NON-NLS-11$ //$NON-NLS-10$ //$NON-NLS-7$ //$NON-NLS-9$ //$NON-NLS-8$ //$NON-NLS-6$ //$NON-NLS-5$ //$NON-NLS-4$ //$NON-NLS-3$ //$NON-NLS-2$ //$NON-NLS-1$

  /**
   * Create a new javadoc scanner for the given color provider.
   * 
   * @param provider
   *          the color provider
   */
  public SIDLDocumentationScanner(SIDLColorProvider provider) {
    super();

    IToken keyword = new Token(new TextAttribute(
        provider.getColor(SIDLColorProvider.JAVADOC_KEYWORD)));
    IToken tag = new Token(new TextAttribute(
        provider.getColor(SIDLColorProvider.JAVADOC_TAG)));
    IToken link = new Token(new TextAttribute(
        provider.getColor(SIDLColorProvider.JAVADOC_LINK)));

    List<IRule> list = new ArrayList<IRule>();

    // Add rule for tags.
    list.add(new SingleLineRule("<", ">", tag)); //$NON-NLS-2$ //$NON-NLS-1$

    // Add rule for links.
    list.add(new SingleLineRule("{", "}", link)); //$NON-NLS-2$ //$NON-NLS-1$

    // Add generic whitespace rule.
    list.add(new WhitespaceRule(new SIDLWhiteSpaceDetector()));

    // Add word rule for keywords.
    WordRule wordRule = new WordRule(new SIDLDocWordDetector());
    for (String fgKeyword : fgKeywords) {
      wordRule.addWord(fgKeyword, keyword);
    }
    list.add(wordRule);

    IRule[] result = new IRule[list.size()];
    list.toArray(result);
    setRules(result);
  }
}
