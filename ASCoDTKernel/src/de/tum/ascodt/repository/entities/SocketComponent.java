package de.tum.ascodt.repository.entities;

import de.tum.ascodt.utils.exceptions.ASCoDTException;


public interface SocketComponent {
	public void open() throws ASCoDTException;
	public void close() throws ASCoDTException;;
	public String getHost();
	public int getPort();
}
