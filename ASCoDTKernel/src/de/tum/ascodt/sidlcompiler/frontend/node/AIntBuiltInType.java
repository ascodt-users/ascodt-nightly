/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;


import de.tum.ascodt.sidlcompiler.frontend.analysis.Analysis;


@SuppressWarnings("nls")
public final class AIntBuiltInType extends PBuiltInType {

  public AIntBuiltInType() {
    // Constructor
  }

  @Override
  public void apply(Switch sw) {
    ((Analysis)sw).caseAIntBuiltInType(this);
  }

  @Override
  public Object clone() {
    return new AIntBuiltInType();
  }

  @Override
  void removeChild(@SuppressWarnings("unused") Node child) {
    // Remove child
    throw new RuntimeException("Not a child.");
  }

  @Override
  void replaceChild(@SuppressWarnings("unused") Node oldChild,
                    @SuppressWarnings("unused") Node newChild) {
    // Replace child
    throw new RuntimeException("Not a child.");
  }

  @Override
  public String toString() {
    return "";
  }
}
