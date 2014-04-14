package de.tum.ascodt.plugin.utils.exceptions;


import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Calendar;

import de.tum.ascodt.utils.ConsoleDevice;


/**
 * Error Writer Device
 * 
 * The error writer device basically is a singleton (single point of contact)
 * to write error messages. It forwards error messages to an ASCoDT console,
 * and open a message box displaying the error. Furthermore, it logs the
 * message into an output file.
 * 
 * @author Atanas Atanasov, Tobias Weinzierl
 */
public class ErrorWriterDevice {
  private static ErrorWriterDevice _singleton = new ErrorWriterDevice();

  private static String date() {
    return new SimpleDateFormat("yyyy.MM.dd").format(Calendar.getInstance()
        .getTime());
  }

  public static ErrorWriterDevice getInstance() {
    return _singleton;
  }

  private static String time() {
    return new SimpleDateFormat("HH:mm:ss").format(Calendar.getInstance()
        .getTime());
  }

  private FileWriter _fileWriter;

  private BufferedWriter _errorLog;

  private ErrorWriterDevice() {
    try {
      File errorLogFile = new File("ErrorLog.log");
      if (errorLogFile.exists()) {
        errorLogFile.delete();
      }
      errorLogFile.createNewFile();
      _fileWriter = new FileWriter(errorLogFile, true);
      _errorLog = new BufferedWriter(_fileWriter);
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public void print(String message) {
    print(new Exception().getStackTrace()[1].toString(), message);
  }

  private void print(String trace, String message) {
    StringBuilder sb = new StringBuilder();

    sb.append("[");
    sb.append(date());
    sb.append("]");
    sb.append("[");
    sb.append(time());
    sb.append("]");
    sb.append("[");
    sb.append("Error");
    sb.append("]");
    sb.append("[");
    sb.append(trace);
    sb.append("]");
    sb.append(":");
    sb.append(" ");
    sb.append(message);

    String log = sb.toString();

    try {
      _errorLog.write(log);
      _errorLog.flush();
    } catch (IOException e) {
      e.printStackTrace();
    }

    ConsoleDevice.getInstance().getConsole("ASCoDT Error").print(log);
  }

  public void print(Throwable throwable) {
    print(new Exception().getStackTrace()[1].toString(), throwable != null
        ? throwable.getMessage() : "");

    if (throwable != null) {
      throwable.printStackTrace(new PrintWriter(_fileWriter));
      throwable.printStackTrace();
    }
  }

  public void println(String message) {
    println(new Exception().getStackTrace()[1].toString(), message);
  }

  private void println(String trace, String message) {
    print(trace, message + "\n");
  }

  public void println(Throwable throwable) {
    println(new Exception().getStackTrace()[1].toString(), throwable != null
        ? throwable.getMessage() : "");

    if (throwable != null) {
      throwable.printStackTrace(new PrintWriter(_fileWriter));
      throwable.printStackTrace();
    }
  }
}
