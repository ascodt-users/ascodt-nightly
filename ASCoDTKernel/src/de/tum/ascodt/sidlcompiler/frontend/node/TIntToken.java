/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;

import de.tum.ascodt.sidlcompiler.frontend.analysis.*;

@SuppressWarnings("nls")
public final class TIntToken extends Token
{
    public TIntToken()
    {
        super.setText("int");
    }

    public TIntToken(int line, int pos)
    {
        super.setText("int");
        setLine(line);
        setPos(pos);
    }

    @Override
    public Object clone()
    {
      return new TIntToken(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTIntToken(this);
    }

    @Override
    public void setText(@SuppressWarnings("unused") String text)
    {
        throw new RuntimeException("Cannot change TIntToken text.");
    }
}
