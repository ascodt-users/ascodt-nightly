package de.tum.ascodt.utils;


/**
 * @author Atanas Atanasov
 *         A standard output device which forwards printing calls to
 *         System.out.
 * 
 */
public class StdOutputDevice implements OutputDevice {
  @Override
  public void print(String string) {
    System.out.print(string);
  }

  @Override
  public void println(String line) {
    System.out.println(line);
  }
}
