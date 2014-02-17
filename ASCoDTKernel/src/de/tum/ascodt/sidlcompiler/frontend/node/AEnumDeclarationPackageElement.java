/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;


import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

import de.tum.ascodt.sidlcompiler.frontend.analysis.Analysis;


@SuppressWarnings("nls")
public final class AEnumDeclarationPackageElement extends PPackageElement {
  private TIdentifier _name_;
  private final LinkedList<PEnumerator> _enumerator_ = new LinkedList<PEnumerator>();

  public AEnumDeclarationPackageElement() {
    // Constructor
  }

  public AEnumDeclarationPackageElement(
      @SuppressWarnings("hiding") TIdentifier _name_,
      @SuppressWarnings("hiding") List<PEnumerator> _enumerator_) {
    // Constructor
    setName(_name_);

    setEnumerator(_enumerator_);

  }

  @Override
  public void apply(Switch sw) {
    ((Analysis)sw).caseAEnumDeclarationPackageElement(this);
  }

  @Override
  public Object clone() {
    return new AEnumDeclarationPackageElement(cloneNode(_name_),
        cloneList(_enumerator_));
  }

  public LinkedList<PEnumerator> getEnumerator() {
    return _enumerator_;
  }

  public TIdentifier getName() {
    return _name_;
  }

  @Override
  void removeChild(@SuppressWarnings("unused") Node child) {
    // Remove child
    if (_name_ == child) {
      _name_ = null;
      return;
    }

    if (_enumerator_.remove(child)) {
      return;
    }

    throw new RuntimeException("Not a child.");
  }

  @Override
  void replaceChild(@SuppressWarnings("unused") Node oldChild,
      @SuppressWarnings("unused") Node newChild) {
    // Replace child
    if (_name_ == oldChild) {
      setName((TIdentifier)newChild);
      return;
    }

    for (ListIterator<PEnumerator> i = _enumerator_.listIterator(); i.hasNext();) {
      if (i.next() == oldChild) {
        if (newChild != null) {
          i.set((PEnumerator)newChild);
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

  public void setEnumerator(List<PEnumerator> list) {
    _enumerator_.clear();
    _enumerator_.addAll(list);
    for (PEnumerator e : list) {
      if (e.parent() != null) {
        e.parent().removeChild(e);
      }

      e.parent(this);
    }
  }

  public void setName(TIdentifier node) {
    if (_name_ != null) {
      _name_.parent(null);
    }

    if (node != null) {
      if (node.parent() != null) {
        node.parent().removeChild(node);
      }

      node.parent(this);
    }

    _name_ = node;
  }

  @Override
  public String toString() {
    return "" + toString(_name_) + toString(_enumerator_);
  }
}
