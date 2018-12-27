#pragma once

#include <RengaScript/GeometryTypes.h>

// TODO: create template, remove code duplication for 3D
class Curve2DStub : public ICurve2D
{
public:
  Curve2DStub()
  {}

  Curve2DStub(int id_)
    : id(id_)
  {}
  
  Curve2DStub(const Curve2DStub&) = default;
  Curve2DStub(Curve2DStub&&) = default;

  ICurve2D* copy() const override
  {
    return new Curve2DStub(id);
  }

  ICurve2D* getUnionWith(const ICurve2D* pOther) const override
  {
    auto pOtherStub = dynamic_cast<const Curve2DStub*>(pOther);
    assert(pOther);
    return new Curve2DStub(id + pOtherStub->id);
  }

public:
  int id = 0;
};

class Curve3DStub : public ICurve3D
{
public:
  Curve3DStub()
  {}

  Curve3DStub(int id_)
    : id(id_)
  {}

  Curve3DStub(const Curve3DStub&) = default;
  Curve3DStub(Curve3DStub&&) = default;

  ICurve3D* copy() const override
  {
    return new Curve3DStub(id);
  }

public:
  int id = 0;
};

class SolidStub : public ISolid
{
public:
  SolidStub()
  {}

  SolidStub(int id_)
    : id(id_)
  {}

  SolidStub(const SolidStub&) = default;
  SolidStub(SolidStub&&) = default;

  ISolid* copy() const override
  {
    return new SolidStub(id);
  }

  ISolid* getMultisolidWith(const ISolid* pOther) const override
  {
    auto pOtherStub = dynamic_cast<const SolidStub*>(pOther);
    assert(pOther);
    return new SolidStub(10 * (id + pOtherStub->id)); // just to separate from getUnionWith
  }

  ISolid* getUnionWith(const ISolid* pOther) const override
  {
    auto pOtherStub = dynamic_cast<const SolidStub*>(pOther);
    assert(pOther);
    return new SolidStub(id + pOtherStub->id);
  }

  ISolid* getDifferenceWith(const ISolid* pOther) const
  {
    auto pOtherStub = dynamic_cast<const SolidStub*>(pOther);
    assert(pOther);
    return new SolidStub(id - pOtherStub->id);
  }

public:
  int id = 0;
};

class LCSStub : public ILCS
{
public:
  LCSStub()
  {}

  LCSStub(int id_)
    : id(id_)
  {}

  LCSStub(const LCSStub&) = default;
  LCSStub(LCSStub&&) = default;

  ILCS* copy() const override
  {
    return new LCSStub(id);
  }

public:
  int id = 0;
};
