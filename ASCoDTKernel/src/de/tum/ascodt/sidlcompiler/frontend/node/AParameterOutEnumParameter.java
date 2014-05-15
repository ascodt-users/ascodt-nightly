/* This file was generated by SableCC (http://www.sablecc.org/). */

package de.tum.ascodt.sidlcompiler.frontend.node;


import de.tum.ascodt.sidlcompiler.frontend.analysis.Analysis;


@SuppressWarnings("nls")
public final class AParameterOutEnumParameter extends PParameter {
  private PUserDefinedType _type_;
  private TIdentifier _name_;

  public AParameterOutEnumParameter() {
    // Constructor
  }

  public AParameterOutEnumParameter(@SuppressWarnings("hiding") PUserDefinedType _type_,
                                    @SuppressWarnings("hiding") TIdentifier _name_) {
    // Constructor
    setType(_type_);

    setName(_name_);

  }

  @Override
  public void apply(Switch sw) {
    ((Analysis)sw).caseAParameterOutEnumParameter(this);
  }

  @Override
  public Object clone() {
    return new AParameterOutEnumParameter(cloneNode(_type_), cloneNode(_name_));
  }

  public TIdentifier getName() {
    return _name_;
  }

  public PUserDefinedType getType() {
    return _type_;
  }

  @Override
  void removeChild(@SuppressWarnings("unused") Node child) {
    // Remove child
    if (_type_ == child) {
      _type_ = null;
      return;
    }

    if (_name_ == child) {
      _name_ = null;
      return;
    }

    throw new RuntimeException("Not a child.");
  }

  @Override
  void replaceChild(@SuppressWarnings("unused") Node oldChild,
                    @SuppressWarnings("unused") Node newChild) {
    // Replace child
    if (_type_ == oldChild) {
      setType((PUserDefinedType)newChild);
      return;
    }

    if (_name_ == oldChild) {
      setName((TIdentifier)newChild);
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

  public void setType(PUserDefinedType node) {
    if (_type_ != null) {
      _type_.parent(null);
    }

    if (node != null) {
      if (node.parent() != null) {
        node.parent().removeChild(node);
      }

      node.parent(this);
    }

    _type_ = node;
  }

  @Override
  public String toString() {
    return "" + toString(_type_) + toString(_name_);
  }
}
