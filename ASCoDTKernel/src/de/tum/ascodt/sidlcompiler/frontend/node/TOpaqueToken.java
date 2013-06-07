/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;

import de.tum.ascodt.sidlcompiler.frontend.analysis.*;

@SuppressWarnings("nls")
public final class TOpaqueToken extends Token
{
    public TOpaqueToken()
    {
        super.setText("opaque");
    }

    public TOpaqueToken(int line, int pos)
    {
        super.setText("opaque");
        setLine(line);
        setPos(pos);
    }

    @Override
    public Object clone()
    {
      return new TOpaqueToken(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTOpaqueToken(this);
    }

    @Override
    public void setText(@SuppressWarnings("unused") String text)
    {
        throw new RuntimeException("Cannot change TOpaqueToken text.");
    }
}
