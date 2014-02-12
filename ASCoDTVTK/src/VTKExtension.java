import java.io.IOException;
import java.util.Set;

import org.eclipse.core.runtime.Path;
import org.eclipse.jdt.core.IClasspathEntry;
import org.eclipse.jdt.core.JavaCore;

import de.tum.ascodt.plugin.ASCoDTVTKPlugin;
import de.tum.ascodt.plugin.extensions.Project;
import de.tum.ascodt.resources.ResourceManager;


public class VTKExtension implements Project {

	public VTKExtension() {
		// TODO Auto-generated constructor stub
	}

	@Override
	public void addClasspathEntries(Set<IClasspathEntry> classpathEntries) {
		try {
		classpathEntries.add(JavaCore.newLibraryEntry(new Path(ResourceManager.getResourceAsPath("libs/vtk.jar",ASCoDTVTKPlugin.ID).getPath()),null,null,false));
		classpathEntries.add(JavaCore.newLibraryEntry(new Path(ResourceManager.getResourceAsPath("",ASCoDTVTKPlugin.ID).getPath()),null,null,false));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
