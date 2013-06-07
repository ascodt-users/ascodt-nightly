/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;

import de.tum.ascodt.sidlcompiler.frontend.analysis.*;

@SuppressWarnings("nls")
public final class TImplementsToken extends Token
{
    public TImplementsToken()
    {
        super.setText("implements-all");
    }

    public TImplementsToken(int line, int pos)
    {
        super.setText("implements-all");
        setLine(line);
        setPos(pos);
    }

    @Override
    public Object clone()
    {
      return new TImplementsToken(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTImplementsToken(this);
    }

    @Override
    public void setText(@SuppressWarnings("unused") String text)
    {
        throw new RuntimeException("Cannot change TImplementsToken text.");
    }
}
