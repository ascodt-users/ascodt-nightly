package de.tum.ascodt.plugin.project;

import java.io.IOException;
import java.util.Set;


import de.tum.ascodt.plugin.ASCoDTVTKPlugin;
import de.tum.ascodt.plugin.extensions.Project;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.resources.ResourceManager;
import de.tum.ascodt.utils.exceptions.ASCoDTException;

import org.eclipse.core.runtime.Path;
import org.eclipse.jdt.core.IClasspathEntry;
import org.eclipse.jdt.core.JavaCore;
public class ProjectVTKExtension implements Project {
	private Trace _trace = new Trace(Project.class.getCanonicalName());
	public ProjectVTKExtension() {
		
	}

	
	@Override
	public void addClasspathEntries(Set<IClasspathEntry> classpathEntries) throws ASCoDTException {
		_trace.in("addClasspathEntries()");
		try {
			classpathEntries.add(JavaCore.newLibraryEntry(new Path(ResourceManager.getResourceAsPath("third-party-libs/vtk.jar",ASCoDTVTKPlugin.ID).getPath()),null,null,false));
			classpathEntries.add(JavaCore.newLibraryEntry(new Path(ResourceManager.getResourceAsPath("",ASCoDTVTKPlugin.ID).getPath()),null,null,false));
		
		} catch (IOException e) {
			throw new ASCoDTException(ProjectVTKExtension.class.getCanonicalName(),"addClasspathEntries()",e.getLocalizedMessage(),e);
		}
		_trace.out("addClasspathEntries()");
		
	}

}
