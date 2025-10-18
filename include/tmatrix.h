// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size exceeds maximum");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size exceeds maximum");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }

  //Конструктор копирования
  TDynamicVector(const TDynamicVector& v) :sz(v.sz)
  {
      pMem = new T[sz];
      copy(v.pMem, v.pMem + sz, pMem);
  }

  //Конструктор перемещения
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
      v.sz = 0;
      v.pMem = nullptr;
  }

  //Деструктор
  ~TDynamicVector()
  {
      if (pMem != nullptr) {
          delete[] pMem;
          pMem = nullptr;
      }
      sz = 0;
  }

  //Оператор присваивания (копирование)
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          if (sz != v.sz) {
              delete[] pMem;
              sz = v.sz;
              pMem = new T[sz];
          }
          copy(v.pMem, v.pMem + sz, pMem);
      }
      return *this;
  }

  //Оператор присваивания (перемещение)
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.sz = 0;
          v.pMem = nullptr;
      }
      return *this;
  }

  //получение размера вектора
  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind > sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind > sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i])
              return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector<T> operator+(T val)
  {
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; i++)
          result.pMem[i] = pMem[i] + val;
      return result;
  }
  TDynamicVector<T> operator-(T val)
  {
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; i++)
          result.pMem[i] = pMem[i] - val;
      return result;
  }
  TDynamicVector<T> operator*(T val)
  {
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; i++)
          result.pMem[i] = pMem[i] * val;
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw invalid_argument("Vector must have same size ffor addition");
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++)
          result.pMem[i] = pMem[i] + v.pMem[i];
      return result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw invalid_argument("Vector must have same size ffor addition");
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++)
          result.pMem[i] = pMem[i] - v.pMem[i];
      return result;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw invalid_argument("Vector must have same size ffor addition");
      T result = T();
      for (size_t i = 0; i < sz; i++)
          result += pMem[i] * v.pMem[i];
      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s > MAX_MATRIX_SIZE)
      throw out_of_range("Matrix size exceeds maximum");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }
  TDynamicMatrix(const TDynamicMatrix& m) : TDynamicVector<TDynamicVector<T>>(m.sz)
  {
      for (size_t i = 0; i < sz; i++)
          pMem[i] = m.pMem[i];
  }
  TDynamicMatrix& operator=(const TDynamicMatrix& m)
  {
      if (this != &m) {
          if (sz != m.sz) {
              TDynamicVector<TDynamicVector<T>>::operator=(m);
          }
          else {
              for (size_t i = 0; i < sz; i++)
                  pMem[i] = m.pMem[i];
          }
      }
      return *this;
  }

  // Оператор неравенства (тоже нужно добавить)
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // Получение размера матрицы (квадратная, поэтому один размер)
  size_t size() const noexcept { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i])
              return false;
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++)
          result[i] = pMem[i] * val;
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size())
          throw invalid_argument("Matrix and vector sizes don't match for multiplication");
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; i++)
          result[i] = pMem[i] * v;
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw invalid_argument("Matrix must have same size for addition");
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++)
          result[i] = pMem[i] + m.pMem[i];
      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw invalid_argument("Matrix must have same size for addition");
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++)
          result[i] = pMem[i] - m.pMem[i];
      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw invalid_argument("Matrices must have same size for multiplication");
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              T sum = T();
              for (size_t k = 0; k < sz; k++)
                  sum += pMem[i][k] * m.pMem[k][j];
              result[i][j] = sum;
          }
      }
      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < m.sz; i++)
          istr >> m.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < m.sz; i++) {
          ostr << m.pMem[i];
          if (i != m.sz - 1)
              ostr << endl;
      }
      return ostr;
  }
};

#endif
