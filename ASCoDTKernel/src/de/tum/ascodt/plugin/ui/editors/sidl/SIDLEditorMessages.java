package de.tum.ascodt.plugin.ui.editors.sidl;


import java.util.MissingResourceException;
import java.util.ResourceBundle;


public class SIDLEditorMessages {

  private static final String RESOURCE_BUNDLE =
      "de.tum.ascodt.plugin.SIDLEditorMessages"; //$NON-NLS-1$

  private static ResourceBundle fgResourceBundle =
      ResourceBundle.getBundle(RESOURCE_BUNDLE);

  public static ResourceBundle getResourceBundle() {
    return fgResourceBundle;
  }

  public static String getString(String key) {
    try {
      return fgResourceBundle.getString(key);
    } catch (MissingResourceException e) {
      return "!" + key + "!";//$NON-NLS-2$ //$NON-NLS-1$
    }
  }

  private SIDLEditorMessages() {}
}
