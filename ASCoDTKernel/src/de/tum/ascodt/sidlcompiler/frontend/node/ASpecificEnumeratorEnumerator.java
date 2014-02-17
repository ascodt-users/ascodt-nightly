/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;


import de.tum.ascodt.sidlcompiler.frontend.analysis.Analysis;


@SuppressWarnings("nls")
public final class ASpecificEnumeratorEnumerator extends PEnumerator {
  private TIdentifier _name_;
  private TConstant _value_;

  public ASpecificEnumeratorEnumerator() {
    // Constructor
  }

  public ASpecificEnumeratorEnumerator(
      @SuppressWarnings("hiding") TIdentifier _name_,
      @SuppressWarnings("hiding") TConstant _value_) {
    // Constructor
    setName(_name_);

    setValue(_value_);

  }

  @Override
  public void apply(Switch sw) {
    ((Analysis)sw).caseASpecificEnumeratorEnumerator(this);
  }

  @Override
  public Object clone() {
    return new ASpecificEnumeratorEnumerator(cloneNode(_name_),
        cloneNode(_value_));
  }

  public TIdentifier getName() {
    return _name_;
  }

  public TConstant getValue() {
    return _value_;
  }

  @Override
  void removeChild(@SuppressWarnings("unused") Node child) {
    // Remove child
    if (_name_ == child) {
      _name_ = null;
      return;
    }

    if (_value_ == child) {
      _value_ = null;
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

    if (_value_ == oldChild) {
      setValue((TConstant)newChild);
      return;
    }

    throw new RuntimeException("Not a child.");
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

  public void setValue(TConstant node) {
    if (_value_ != null) {
      _value_.parent(null);
    }

    if (node != null) {
      if (node.parent() != null) {
        node.parent().removeChild(node);
      }

      node.parent(this);
    }

    _value_ = node;
  }

  @Override
  public String toString() {
    return "" + toString(_name_) + toString(_value_);
  }
}
