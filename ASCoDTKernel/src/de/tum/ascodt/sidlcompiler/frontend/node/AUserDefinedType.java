/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;


import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

import de.tum.ascodt.sidlcompiler.frontend.analysis.Analysis;


@SuppressWarnings("nls")
public final class AUserDefinedType extends PUserDefinedType {
  private final LinkedList<TIdentifier> _identifier_ =
      new LinkedList<TIdentifier>();

  public AUserDefinedType() {
    // Constructor
  }

  public AUserDefinedType(@SuppressWarnings("hiding") List<TIdentifier> _identifier_) {
    // Constructor
    setIdentifier(_identifier_);

  }

  @Override
  public void apply(Switch sw) {
    ((Analysis)sw).caseAUserDefinedType(this);
  }

  @Override
  public Object clone() {
    return new AUserDefinedType(cloneList(_identifier_));
  }

  public LinkedList<TIdentifier> getIdentifier() {
    return _identifier_;
  }

  @Override
  void removeChild(@SuppressWarnings("unused") Node child) {
    // Remove child
    if (_identifier_.remove(child)) {
      return;
    }

    throw new RuntimeException("Not a child.");
  }

  @Override
  void replaceChild(@SuppressWarnings("unused") Node oldChild,
                    @SuppressWarnings("unused") Node newChild) {
    // Replace child
    for (ListIterator<TIdentifier> i = _identifier_.listIterator(); i.hasNext();) {
      if (i.next() == oldChild) {
        if (newChild != null) {
          i.set((TIdentifier)newChild);
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

  public void setIdentifier(List<TIdentifier> list) {
    _identifier_.clear();
    _identifier_.addAll(list);
    for (TIdentifier e : list) {
      if (e.parent() != null) {
        e.parent().removeChild(e);
      }

      e.parent(this);
    }
  }

  @Override
  public String toString() {
    return "" + toString(_identifier_);
  }
}
