package de.tum.ascodt.resources;


import java.io.IOException;
import java.io.InputStream;
import java.net.URISyntaxException;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.eclipse.core.runtime.FileLocator;
import org.eclipse.core.runtime.Platform;


/**
 * through this class the plugin has access to the internal resource file like
 * icons, templates, etc..
 * 
 * @author atanasoa
 * 
 */
public class ResourceManager {
  public static Path getResourceAsPath(String pathString, String plugin) throws IOException {
    if (Platform.getBundle(plugin) != null) {
      boolean hasDebugDirectory = false;

      if (FileLocator.find(Platform.getBundle(plugin),
                           new org.eclipse.core.runtime.Path("debug"),
                           null) != null) {
        hasDebugDirectory = true;
      }

      try {
        return Paths.get(FileLocator.toFileURL(FileLocator.find(Platform.getBundle(plugin),
                                                                new org.eclipse.core.runtime.Path((hasDebugDirectory
                                                                                                                    ? "debug" + org.eclipse.core.runtime.Path.SEPARATOR
                                                                                                                    : "") + pathString),
                                                                null))
                                    .toURI());
      } catch (URISyntaxException e) {}
    }

    return null;
  }

  /**
   * returns a resource located inside of the plugin
   * 
   * @param pathToResource
   *          relative path to the resource to be found (example:
   *          de/tum/ascodt/resources/)
   * @return
   * @throws IOException
   */
  public static InputStream getResourceAsStream(Path path, String plugin) throws IOException {
    return ResourceManager.class.getResourceAsStream(path.toString());
  }
}
