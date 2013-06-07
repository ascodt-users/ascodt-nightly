/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;

import java.util.*;
import de.tum.ascodt.sidlcompiler.frontend.analysis.*;

@SuppressWarnings("nls")
public final class AOperation extends POperation
{
    private TIdentifier _name_;
    private final LinkedList<PParameter> _parameter_ = new LinkedList<PParameter>();

    public AOperation()
    {
        // Constructor
    }

    public AOperation(
        @SuppressWarnings("hiding") TIdentifier _name_,
        @SuppressWarnings("hiding") List<PParameter> _parameter_)
    {
        // Constructor
        setName(_name_);

        setParameter(_parameter_);

    }

    @Override
    public Object clone()
    {
        return new AOperation(
            cloneNode(this._name_),
            cloneList(this._parameter_));
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseAOperation(this);
    }

    public TIdentifier getName()
    {
        return this._name_;
    }

    public void setName(TIdentifier node)
    {
        if(this._name_ != null)
        {
            this._name_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        this._name_ = node;
    }

    public LinkedList<PParameter> getParameter()
    {
        return this._parameter_;
    }

    public void setParameter(List<PParameter> list)
    {
        this._parameter_.clear();
        this._parameter_.addAll(list);
        for(PParameter e : list)
        {
            if(e.parent() != null)
            {
                e.parent().removeChild(e);
            }

            e.parent(this);
        }
    }

    @Override
    public String toString()
    {
        return ""
            + toString(this._name_)
            + toString(this._parameter_);
    }

    @Override
    void removeChild(@SuppressWarnings("unused") Node child)
    {
        // Remove child
        if(this._name_ == child)
        {
            this._name_ = null;
            return;
        }

        if(this._parameter_.remove(child))
        {
            return;
        }

        throw new RuntimeException("Not a child.");
    }

    @Override
    void replaceChild(@SuppressWarnings("unused") Node oldChild, @SuppressWarnings("unused") Node newChild)
    {
        // Replace child
        if(this._name_ == oldChild)
        {
            setName((TIdentifier) newChild);
            return;
        }

        for(ListIterator<PParameter> i = this._parameter_.listIterator(); i.hasNext();)
        {
            if(i.next() == oldChild)
            {
                if(newChild != null)
                {
                    i.set((PParameter) newChild);
                    newChild.parent(this);
                    oldChild.parent(null);
                    return;
                }

                i.remove();
                oldChild.parent(null);
                return;
            }
        }

        throw new RuntimeException("Not a child.");
    }
}