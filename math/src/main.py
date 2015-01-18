#!/usr/bin/python

class Matrix:
  def __init__(self, n = 1, m = 1, v = 0):
    self.n, self.m = n, m
    self.data = [[v]*m for _ in xrange(0, n)]

  def __getitem__(self, n):
    return self.data[n]

  def __imul__(self, s):
    self.data = map(
        lambda xs: map(
          lambda x: s*x,
          xs),
        self.data)
    return self

  def __add__(self, rhs):
    if self.n != rhs.n or self.m != rhs.m:
      raise Exception("noncompatible size: lhs=%s rhs=%s"%(self.data, rhs.data))
    res = Matrix(self.n, self.m)
    res.data = map(
        lambda p: map(
          lambda p: p[0]+p[1],
          zip(p[0], p[1])),
        zip(self.data, rhs.data))
    return res

  def __repr__(self):
    return repr(self.__dict__)

  def transpose(self):
    res = Matrix(self.m, self.n)
    for i in xrange(0, self.n):
      for j in xrange(0, self.m):
        res[j][i] = self[i][j];
    return res

  def __mul__(self, rhs):
    if self.m != rhs.n:
      raise Exception("noncompatible size: lhs=%s rhs=%s"%(self, rhs))
    res = Matrix(self.n, rhs.m)
    for i in xrange(0, self.n):
      for j in xrange(0, self.m):
        for k in xrange(0, self.m):
          res[i][j] = self[i][k]*rhs[k][j]
    return res

lhs = Matrix(2, 3, 1)
rhs = Matrix(3, 2, 1)
res = lhs*rhs
print(res)
