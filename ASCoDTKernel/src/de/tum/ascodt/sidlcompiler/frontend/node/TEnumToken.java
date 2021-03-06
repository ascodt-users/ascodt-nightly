/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;


import de.tum.ascodt.sidlcompiler.frontend.analysis.Analysis;


@SuppressWarnings("nls")
public final class TEnumToken extends Token {
  public TEnumToken() {
    super.setText("enum");
  }

  public TEnumToken(int line, int pos) {
    super.setText("enum");
    setLine(line);
    setPos(pos);
  }

  @Override
  public void apply(Switch sw) {
    ((Analysis)sw).caseTEnumToken(this);
  }

  @Override
  public Object clone() {
    return new TEnumToken(getLine(), getPos());
  }

  @Override
  public void setText(@SuppressWarnings("unused") String text) {
    throw new RuntimeException("Cannot change TEnumToken text.");
  }
}
