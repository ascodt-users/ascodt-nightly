package de.tum.ascodt.repository;


/**
 * Represents target information. Currently ASCoDT supports
 * three targets : a local java component, a local native component and
 * a remote native component connected through sockets.
 * 
 * 
 * @author Tobias Weinzierl
 */
public class Target {
  public enum TargetType {
    JavaLocal {
      @Override
      public String toString() {
        return "java_local";
      }
    },
    JavaNative {
      @Override
      public String toString() {
        return "java_native";
      }
    },

    CxxRemoteSocket {
      @Override
      public String toString() {
        return "cxx_remote_socket";
      }
    },
    FortranRemoteSocket {
      @Override
      public String toString() {
        return "fortran_remote_socket";
      }
    },

    FortranNative {
      @Override
      public String toString() {
        return "fortran_native";
      }
    }

  }

  public static Target createCxxNativeTarget() {
    Target result = new Target();
    result._targetType = TargetType.JavaNative;
    return result;
  }

  public static Target createCxxRemoteSocketTarget() {
    Target result = new Target();
    result._targetType = TargetType.CxxRemoteSocket;
    return result;
  }

  public static Target createFortranNativeTarget() {
    Target result = new Target();
    result._targetType = TargetType.FortranNative;
    return result;
  }

  public static Target createFortranRemoteSocketTarget() {
    Target result = new Target();
    result._targetType = TargetType.FortranRemoteSocket;
    return result;
  }

  /**
   * Factory mechanism
   */
  public static Target createJavaLocalTarget() {
    Target result = new Target();
    result._targetType = TargetType.JavaLocal;
    return result;
  }

  public static Target createTarget(String identifier) {
    Target result = null;
    if (identifier.equals(TargetType.JavaLocal.toString())) {
      result = createJavaLocalTarget();
    } else if (identifier.equals(TargetType.JavaNative.toString())) {
      result = createCxxNativeTarget();
    } else if (identifier.equals(TargetType.CxxRemoteSocket.toString())) {
      result = createCxxRemoteSocketTarget();
    } else if (identifier.equals(TargetType.FortranNative.toString())) {
      result = createFortranNativeTarget();
    } else if (identifier.equals(TargetType.FortranRemoteSocket.toString())) {
      result = createFortranRemoteSocketTarget();
    }
    return result;
  }

  /**
   * 
   * @return all possible targets
   */
  public static String[] getAllTargetTypes() {
    String[] res = new String[TargetType.values().length];
    for (int i = 0; i < res.length; i++) {
      res[i] = TargetType.values()[i].toString();
    }
    return res;
  }

  public static boolean isCxxNative(String identifier) {
    return identifier.equals(TargetType.JavaNative.toString());
  }

  public static boolean isCxxRemoteSocket(String identifier) {
    return identifier.equals(TargetType.CxxRemoteSocket.toString());
  }

  public static boolean isFortranNative(String identifier) {
    return identifier.equals(TargetType.FortranNative.toString());
  }

  public static boolean isFortranRemoteSocket(String identifier) {
    return identifier.equals(TargetType.FortranRemoteSocket.toString());
  }

  public static boolean isJavaLocal(String identifier) {
    return identifier.equals(TargetType.JavaLocal.toString());
  }

  /**
   * This method verifies validity of targets
   * 
   * @param identifier
   * @return
   */
  public static boolean isValidTarget(String identifier) {
    return isJavaLocal(identifier) || isCxxNative(identifier) ||
        isFortranRemoteSocket(identifier) || isCxxRemoteSocket(identifier) ||
        isFortranNative(identifier);
  }

  private TargetType _targetType;

  private Object _descriptionObject;

  private Target() {}

  public Object getDescription() {
    return _descriptionObject;
  }

  public TargetType getType() {
    return _targetType;
  }

}
