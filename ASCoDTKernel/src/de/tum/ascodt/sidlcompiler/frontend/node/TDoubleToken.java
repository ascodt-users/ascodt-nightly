/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;


import de.tum.ascodt.sidlcompiler.frontend.analysis.Analysis;


@SuppressWarnings("nls")
public final class TDoubleToken extends Token {
  public TDoubleToken() {
    super.setText("double");
  }

  public TDoubleToken(int line, int pos) {
    super.setText("double");
    setLine(line);
    setPos(pos);
  }

  @Override
  public void apply(Switch sw) {
    ((Analysis)sw).caseTDoubleToken(this);
  }

  @Override
  public Object clone() {
    return new TDoubleToken(getLine(), getPos());
  }

  @Override
  public void setText(@SuppressWarnings("unused") String text) {
    throw new RuntimeException("Cannot change TDoubleToken text.");
  }
}
