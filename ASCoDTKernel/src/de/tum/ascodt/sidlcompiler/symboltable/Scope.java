// Copyright (C) 2009 Technische Universitaet Muenchen
// This file is part of the ASCoDT project. For conditions of distribution and
// use, please see the copyright notice at www5.in.tum.de/ascodt
package de.tum.ascodt.sidlcompiler.symboltable;


import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AEnumDeclarationPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AInterfacePackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AUserDefinedType;
import de.tum.ascodt.sidlcompiler.frontend.node.Node;
import de.tum.ascodt.sidlcompiler.frontend.node.TIdentifier;


/**
 * One Scope
 * 
 * A scope represents the following information:
 * 
 * - Each scope corresponds to one package
 * - A scope holds the information into which scope it is embedded into
 * - A scope knows its subscopes corresponding to subpackages
 * - Each scope is aware of all symbols, i.e. classes and interfaces, defines
 * within the corresponding package
 * - Each scope knows the file where it has been defined first
 * 
 * @author Tobias Weinzierl
 */
public class Scope {
  /**
   * @return Unqualified identifier of this symbol.
   */
  public static String getSymbol(AClassPackageElement newEntry) {
    return newEntry.getName().getText();
  }

  /**
   * @return Unqualified identifier of this symbol.
   */
  public static String getSymbol(AEnumDeclarationPackageElement newEntry) {
    return newEntry.getName().getText();
  }

  /**
   * @return Unqualified identifier of this symbol.
   */
  public static String getSymbol(AInterfacePackageElement newEntry) {
    return newEntry.getName().getText();
  }

  /**
   * Gives you the symbol of a user defined type. Entries are separated by .
   * 
   * @param node
   * @return
   */
  public static String getSymbol(AUserDefinedType node) {
    String fullQualifiedSymbol = "";
    for (TIdentifier id : node.getIdentifier()) {
      fullQualifiedSymbol += ".";
      fullQualifiedSymbol += id.getText();
    }
    return fullQualifiedSymbol.substring(1);
    // return node.getIdentifier().getLast().getText();
  }

  public static String getSymbol(Node node) {
    if (node instanceof AInterfacePackageElement) {
      return getSymbol((AInterfacePackageElement)node);
    }
    if (node instanceof AEnumDeclarationPackageElement) {
      return getSymbol((AEnumDeclarationPackageElement)node);
    }
    if (node instanceof AClassPackageElement) {
      return getSymbol((AClassPackageElement)node);
    }
    if (node instanceof AUserDefinedType) {
      return getSymbol((AUserDefinedType)node);
    }

    return node.toString();
  }

  /**
   * Pointer to the super scope
   */
  private Scope _superScope;
  private String _nameOfDefiningFile;
  /**
   * Pointer to the super scope
   */
  private Map<String, Scope> _subScope;
  /**
   * A scope's identifier might not contain a dot and has to start with a
   * character. This thing equals "" for the root node. See getFullIdentifier()
   * that has to handle this case explicitly.
   */
  private String _identifier;

  /**
   * The content of the symbol table.
   */
  private Map<String, AClassPackageElement> _classSymbols;

  private Map<AClassPackageElement, String> _classSymbolsFiles;

  private Map<String, AInterfacePackageElement> _interfaceSymbols;

  private Map<String, AEnumDeclarationPackageElement> _enumSymbols;

  /**
   * Holds error message corresponding to this scope. If the message equals "",
   * the scope is valid.
   */
  private String _errorMessage;

  /**
   * For the Root Scope
   */
  public Scope() {
    _identifier = "";
    _superScope = null;
    _classSymbols = new HashMap<String, AClassPackageElement>();
    _interfaceSymbols = new HashMap<String, AInterfacePackageElement>();
    _enumSymbols = new HashMap<String, AEnumDeclarationPackageElement>();
    _subScope = new HashMap<String, Scope>();
  }

  public Scope(Scope old) {
    if (old != null) {
      _identifier = old._identifier;
      _superScope = new Scope(old._superScope);
      _nameOfDefiningFile = old._nameOfDefiningFile;
      _classSymbols = new HashMap<String, AClassPackageElement>(
          old._classSymbols);
      _interfaceSymbols = new HashMap<String, AInterfacePackageElement>(
          old._interfaceSymbols);
      _enumSymbols = new HashMap<String, AEnumDeclarationPackageElement>(
          old._enumSymbols);
      _classSymbolsFiles = new HashMap<AClassPackageElement, String>(
          old._classSymbolsFiles);
      _subScope = new HashMap<String, Scope>(old._subScope);
      _errorMessage = old._errorMessage;

    } else {
      new Scope();
    }
  }

  /**
   * Construct a New Scope
   * 
   * @param identifier
   *          Name of the scope. It is a dehierarchised identifier,
   *          i.e. it must not contain a dot.
   * @param superScope
   *          Superscope. Might be null.
   */
  protected Scope(String identifier, String definingFile, Scope superScope) {
    assert !identifier.contains(".");
    _identifier = identifier;
    _superScope = superScope;
    _nameOfDefiningFile = definingFile;
    _classSymbols = new HashMap<String, AClassPackageElement>();
    _interfaceSymbols = new HashMap<String, AInterfacePackageElement>();
    _enumSymbols = new HashMap<String, AEnumDeclarationPackageElement>();
    _classSymbolsFiles = new HashMap<AClassPackageElement, String>();
    _subScope = new HashMap<String, Scope>();
    _errorMessage = "";
    if (superScope != null) {
      superScope._subScope.put(_identifier, this);
    }
  }

  /**
   * Add a symbol
   * 
   * This operation is re-entrant-save, i.e. you cannot add a symbol twice. If
   * you try to do so, the second operation becomes nop.
   * 
   * @param newEntry
   * @param fileName
   */
  public void addSymbol(AClassPackageElement newEntry, String fileName) {
    String symbolName = getSymbol(newEntry);

    if (_interfaceSymbols.containsKey(symbolName)) {
      _errorMessage += "Class symbol " + symbolName + " in " + fileName +
          " coincides with interface symbol previously defined in " +
          getDefiningScope(symbolName).getFullIdentifierOfPackage() + "\n";
    } else if (_enumSymbols.containsKey(symbolName)) {
      _errorMessage += "Interface symbol " + symbolName + " in " + fileName +
          " coincides with enum symbol previously defined in " +
          getDefiningScope(symbolName).getFullIdentifierOfPackage() + "\n";
    } else {
      _classSymbols.put(symbolName, newEntry);
    }
  }

  /**
   * Add a symbol
   * 
   * This operation is re-entrant-save, i.e. you cannot add a symbol twice. If
   * you try to do so, the second operation becomes nop.
   * 
   * @param newEntry
   * @param fileName
   */
  public void
      addSymbol(AEnumDeclarationPackageElement newEntry, String fileName) {
    String symbolName = getSymbol(newEntry);

    if (_classSymbols.containsKey(symbolName)) {
      _errorMessage += "Interface symbol " + symbolName + " in " + fileName +
          " coincides with enum symbol previously defined in " +
          getDefiningScope(symbolName).getFullIdentifierOfPackage() + "\n";
    } else if (_interfaceSymbols.containsKey(symbolName)) {
      _errorMessage += "Class symbol " + symbolName + " in " + fileName +
          " coincides with interface symbol previously defined in " +
          getDefiningScope(symbolName).getFullIdentifierOfPackage() + "\n";
    } else {
      _enumSymbols.put(symbolName, newEntry);
    }
  }

  /**
   * Add a symbol
   * 
   * This operation is re-entrant-save, i.e. you cannot add a symbol twice. If
   * you try to do so, the second operation becomes nop.
   * 
   * @param newEntry
   * @param fileName
   */
  public void addSymbol(AInterfacePackageElement newEntry, String fileName) {
    String symbolName = getSymbol(newEntry);

    if (_classSymbols.containsKey(symbolName)) {
      _errorMessage += "Interface symbol " + symbolName + " in " + fileName +
          " coincides with class symbol previously defined in " +
          getDefiningScope(symbolName).getFullIdentifierOfPackage() + "\n";
    } else if (_enumSymbols.containsKey(symbolName)) {
      _errorMessage += "Interface symbol " + symbolName + " in " + fileName +
          " coincides with enum symbol previously defined in " +
          getDefiningScope(symbolName).getFullIdentifierOfPackage() + "\n";
    } else {
      _interfaceSymbols.put(symbolName, newEntry);
    }
  }

  /**
   * Contains a certain sub scope
   * 
   * Is needed by the builder. Whenever it enters a new package, it first has
   * to find out whether this package already exists. If not, it has to create
   * it. Afterwards, the builder uses getSubScope() to continue.
   * 
   * @param identifier
   * @return
   */
  public boolean containsSubScope(String identifier) {
    return _subScope.containsKey(identifier);
  }

  /**
   * Searches for a symbol
   * 
   * Searches for a symbol. If the identifier does not contain a dot, the
   * identifier is local, i.e. we search for the symbol in the local scope. If
   * the identifier starts with a string equaling our identifier, we descend
   * into our subscopes to find an appropiate symbol. Before, we cut away the
   * our identifier. If both cases do not hold, the super scope might know the
   * symbol.
   * 
   * @param identifier
   * @return
   */
  public boolean containsSymbol(String identifier) {
    return getDefiningScope(identifier) != null;
  }

  /**
   * Accepts a type identifier and returns the AST node yielding this
   * definition.
   * 
   * @param identifier
   * @return
   */
  public AClassPackageElement getClassDefinition(String identifier) {
    Scope scope = getDefiningScope(identifier);
    String typeName = identifier.substring(identifier.lastIndexOf(".") + 1);
    if (scope == null) {
      return null;
    }
    return scope._classSymbols.get(typeName);
  }

  String getDefiningFile() {
    return _nameOfDefiningFile;
  }

  /**
   * This operation accepts a string identifier basically giving a package
   * structure. Something like a.b.c. It then returns the corresponding
   * scope.
   * 
   * If the identifier holds a point, it searchers for the scope dfs.
   * See getDefiningScopeDFS(). If this operation doesn't find a class
   * holding identifier, it returns null. In this case, there's only
   * one option: We have to search for the defining scope in the parent
   * scope (else branch).
   * 
   * @param identifier
   *          Always has to be a class or interface name.
   * @return Scope defining a class/interface given by identifier.
   */
  private Scope getDefiningScope(String identifier) {
    Assert.isTrue(identifier.charAt(0) != '.');

    Scope result = getDefiningScopeDFS(identifier);

    if (_identifier.length() == 0 || result != null) {
      return result;
    } else {
      Scope current = this;
      while (current._superScope != null) {
        current = current._superScope;
      }
      return current.getDefiningScope(identifier);
    }
  }

  private Scope getDefiningScopeDFS(String identifier) {
    if (identifier == null) {
      return null;
    }
    if (!identifier.contains(".")) {
      return _enumSymbols.containsKey(identifier) ||
          _classSymbols.containsKey(identifier) ||
          _interfaceSymbols.containsKey(identifier) ? this : null;
    } else {
      String subScope = identifier.substring(0, identifier.indexOf('.'));
      String subIdentifier = identifier.substring(identifier.indexOf('.') + 1);
      return _subScope.containsKey(subScope) ? _subScope.get(subScope)
          .getDefiningScopeDFS(subIdentifier) : null;
    }
  }

  /**
   * Accepts a type identifier and returns the AST node yielding this
   * definition.
   * 
   * @param identifier
   * @return
   */
  public AEnumDeclarationPackageElement getEnumerationDefinition(
      String identifier) {
    Scope scope = getDefiningScope(identifier);
    String typeName = identifier.substring(identifier.lastIndexOf(".") + 1);
    if (scope == null) {
      return null;
    }
    return scope._enumSymbols.get(typeName);
  }

  public String getErrorMessages() {
    String result = _errorMessage;
    for (Scope subScope : _subScope.values()) {
      result += subScope.getErrorMessages();
    }
    return result;
  }

  /**
   * This operation gives you all the classes defined within this scope and
   * all subscopes.
   * 
   * @return
   */
  public Set<AClassPackageElement> getFlattenedClassElements() {
    Set<AClassPackageElement> result = new HashSet<AClassPackageElement>();

    result.addAll(_classSymbols.values());
    for (String subScopeName : _subScope.keySet()) {
      result.addAll(_subScope.get(subScopeName).getFlattenedClassElements());
    }
    return result;
  }

  /**
   * This operation gives you all the enumeration defined within this scope and
   * all subscopes.
   * 
   * @return
   */
  public Set<AEnumDeclarationPackageElement> getFlattenedEnumsElements() {
    Set<AEnumDeclarationPackageElement> result = new HashSet<AEnumDeclarationPackageElement>();

    result.addAll(_enumSymbols.values());
    for (String subScopeName : _subScope.keySet()) {
      result.addAll(_subScope.get(subScopeName).getFlattenedEnumsElements());
    }
    return result;
  }

  /**
   * This operation gives you all the interfaces defined within this scope and
   * all subscopes.
   * 
   * @return
   */
  public Set<AInterfacePackageElement> getFlattenedInterfaceElements() {

    Set<AInterfacePackageElement> result = new TreeSet<AInterfacePackageElement>(
        new Comparator<AInterfacePackageElement>() {

          @Override
          public int compare(AInterfacePackageElement o1,
              AInterfacePackageElement o2) {
            return o1.getName().getText().compareTo(o2.getName().getText());
          }

        });

    result.addAll(_interfaceSymbols.values());
    for (String subScopeName : _subScope.keySet()) {
      result
          .addAll(_subScope.get(subScopeName).getFlattenedInterfaceElements());
    }
    return result;
  }

  /**
   * The full qualifier is basically the namespace with all supernamespaces.
   * 
   * @return Full identifier of this scope.
   */
  public String[] getFullIdentifierOfPackage() {
    if (_superScope == null) {
      return new String[] {};
    } else {
      String[] superNamespaces = _superScope.getFullIdentifierOfPackage();
      String[] result = new String[superNamespaces.length + 1];
      for (int i = 0; i < superNamespaces.length; i++) {
        result[i] = superNamespaces[i];
      }
      result[superNamespaces.length] = _identifier;
      return result;
    }
  }

  /**
   * Takes getFullIdentifier()'s result, concatenates the elements but inserts
   * separator in-between.
   * 
   * @param separator
   *          Typically a "." or a "::".
   * @return
   */
  public String getFullIdentifierOfPackage(String separator) {
    String[] fullIdentifier = getFullIdentifierOfPackage();

    String result = "";
    for (String identifierElement : fullIdentifier) {
      if (!result.isEmpty()) {
        result += separator;
      }
      result += identifierElement;
    }
    return result;
  }

  /**
   * This operation takes a class identifier (either relative or absolute) and
   * returns its full qualified name.
   * 
   * @param identifier
   * @return Full qualified name of identifier which is separated by .
   */
  public String getFullyQualifiedName(String identifier) {
    Scope scope = getDefiningScope(identifier);
    if (scope == null) {
      return null;
    } else {
      String typeName = identifier.substring(identifier.lastIndexOf(".") + 1);
      return scope.getFullIdentifierOfPackage(".") + "." + typeName;
    }
  }

  /**
   * Accepts a type identifier and returns the AST node yielding this
   * definition.
   * 
   * @param identifier
   * @return
   */
  public AInterfacePackageElement getInterfaceDefinition(String identifier) {
    Scope scope = getDefiningScope(identifier);
    String typeName = identifier.substring(identifier.lastIndexOf(".") + 1);
    if (scope == null) {
      return null;
    }
    return scope._interfaceSymbols.get(typeName);
  }

  /**
   * @see containsSubScope()
   */
  public Scope getSubScope(String identifier) {
    return _subScope.get(identifier);
  }

  /**
   * A scope is valid iff there's neither an error corresponding to this
   * package nor to any subscope.
   * 
   * @return scope is valid
   */
  public boolean isValid() {
    boolean result = _errorMessage == "";
    for (Scope subScope : _subScope.values()) {
      result &= subScope.isValid();
    }
    return result;
  }

  public void removeSymbol(AClassPackageElement classEntry) {
    if (_classSymbols.containsKey(classEntry)) {
      _classSymbols.remove(classEntry);
    }
  }

  public void removeSymbol(AEnumDeclarationPackageElement enumEntry) {
    if (_enumSymbols.containsKey(enumEntry)) {
      _enumSymbols.remove(enumEntry);
    }
  }

  public void removeSymbol(AInterfacePackageElement interfaceEntry) {
    if (_interfaceSymbols.containsKey(interfaceEntry)) {
      _interfaceSymbols.remove(interfaceEntry);
    }
  }

  @Override
  public String toString() {
    String result = getFullIdentifierOfPackage(".");
    if (_classSymbols.isEmpty() && _interfaceSymbols.isEmpty()) {
      result += _identifier.length() == 0 ? "[no gobal symbols]"
          : " [no symbols]";
    } else {
      result += ": ";
      for (String symbolName : _interfaceSymbols.keySet()) {
        result += symbolName;
        result += " ";
      }
      for (String symbolName : _classSymbols.keySet()) {
        result += symbolName;
        result += " ";
      }
    }
    result += "\n";
    for (String subScopeName : _subScope.keySet()) {
      result += _subScope.get(subScopeName).toString();
    }
    return result;
  }

}
