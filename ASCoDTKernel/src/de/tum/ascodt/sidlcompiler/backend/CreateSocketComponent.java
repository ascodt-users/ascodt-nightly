package de.tum.ascodt.sidlcompiler.backend;


import java.nio.file.Path;
import java.nio.file.Paths;

import de.tum.ascodt.plugin.services.SocketService;
import de.tum.ascodt.plugin.utils.ProcessListener;
import de.tum.ascodt.repository.entities.SocketComponent;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


public class CreateSocketComponent {
  TemplateFile _templateFileForSocketComponent;

  public CreateSocketComponent(Path componentsDirectoryPath, String[] namespaces) throws ASCoDTException {
    Path path = componentsDirectoryPath.resolve("java");

    for (String namespace : namespaces) {
      path = path.resolve(namespace);
    }

    _templateFileForSocketComponent =
        new TemplateFile(Paths.get("java-abstract-socket-component.template"),
                         path.resolve("SocketComponent.java"),
                         namespaces,
                         TemplateFile.getLanguageConfigurationForJava(),
                         true);

  }

  public void apply() throws ASCoDTException {
    _templateFileForSocketComponent.addMapping("__SOCKET_COMPONENT__",
                                               SocketComponent.class.getCanonicalName());
    _templateFileForSocketComponent.addMapping("__PROCESS_LISTENER__",
                                               ProcessListener.class.getCanonicalName());
    _templateFileForSocketComponent.addMapping("__SOCKET_SERVICE__",
                                               SocketService.class.getCanonicalName());
    _templateFileForSocketComponent.open();
    _templateFileForSocketComponent.close();
  }
}