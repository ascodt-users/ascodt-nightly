/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;

import java.util.*;
import de.tum.ascodt.sidlcompiler.frontend.analysis.*;

@SuppressWarnings("nls")
public final class AInterfacePackageElement extends PPackageElement
{
    private TIdentifier _name_;
    private final LinkedList<PUserDefinedType> _supertype_ = new LinkedList<PUserDefinedType>();
    private final LinkedList<POperation> _operation_ = new LinkedList<POperation>();

    public AInterfacePackageElement()
    {
        // Constructor
    }

    public AInterfacePackageElement(
        @SuppressWarnings("hiding") TIdentifier _name_,
        @SuppressWarnings("hiding") List<PUserDefinedType> _supertype_,
        @SuppressWarnings("hiding") List<POperation> _operation_)
    {
        // Constructor
        setName(_name_);

        setSupertype(_supertype_);

        setOperation(_operation_);

    }

    @Override
    public Object clone()
    {
        return new AInterfacePackageElement(
            cloneNode(this._name_),
            cloneList(this._supertype_),
            cloneList(this._operation_));
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseAInterfacePackageElement(this);
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

    public LinkedList<PUserDefinedType> getSupertype()
    {
        return this._supertype_;
    }

    public void setSupertype(List<PUserDefinedType> list)
    {
        this._supertype_.clear();
        this._supertype_.addAll(list);
        for(PUserDefinedType e : list)
        {
            if(e.parent() != null)
            {
                e.parent().removeChild(e);
            }

            e.parent(this);
        }
    }

    public LinkedList<POperation> getOperation()
    {
        return this._operation_;
    }

    public void setOperation(List<POperation> list)
    {
        this._operation_.clear();
        this._operation_.addAll(list);
        for(POperation e : list)
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
            + toString(this._supertype_)
            + toString(this._operation_);
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

        if(this._supertype_.remove(child))
        {
            return;
        }

        if(this._operation_.remove(child))
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

        for(ListIterator<PUserDefinedType> i = this._supertype_.listIterator(); i.hasNext();)
        {
            if(i.next() == oldChild)
            {
                if(newChild != null)
                {
                    i.set((PUserDefinedType) newChild);
                    newChild.parent(this);
                    oldChild.parent(null);
                    return;
                }

                i.remove();
                oldChild.parent(null);
                return;
            }
        }

        for(ListIterator<POperation> i = this._operation_.listIterator(); i.hasNext();)
        {
            if(i.next() == oldChild)
            {
                if(newChild != null)
                {
                    i.set((POperation) newChild);
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
