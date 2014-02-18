/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;

import de.tum.ascodt.sidlcompiler.frontend.analysis.*;

@SuppressWarnings("nls")
public final class TStringToken extends Token
{
    public TStringToken()
    {
        super.setText("string");
    }

    public TStringToken(int line, int pos)
    {
        super.setText("string");
        setLine(line);
        setPos(pos);
    }

    @Override
    public Object clone()
    {
      return new TStringToken(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTStringToken(this);
    }

    @Override
    public void setText(@SuppressWarnings("unused") String text)
    {
        throw new RuntimeException("Cannot change TStringToken text.");
    }
}
