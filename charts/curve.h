/**
@file curve.h

@brief Объявление класса для кривой графика

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef CURVE_H
#define CURVE_H
//----------------------------------------------------------------------------------
#include <qwt_plot_curve.h>
//----------------------------------------------------------------------------------
class CurveData;
//----------------------------------------------------------------------------------
//! Класс кривой графика
class Curve : public QwtPlotCurve
{
public:
	/**
	 * @brief Curve Конструктор
	 */
    Curve();

	/**
	 * @brief GetCurveData Получить указатель на данные кривой
	 * @return Указатель на данные кривой
	 */
	CurveData *GetCurveData() { return _data; }

	/**
	 * @brief appendPoint Добавить точку на кривую
	 * @param x Координата X
	 * @param y Координата Y
	 */
    void appendPoint(double x, double y);

	/**
	 * @brief appendValue Добавить значение на кривую
	 * @param inc Смещение
	 * @param value Значение
	 */
    void appendValue(double inc, double value);

	/**
	 * @brief setMaxPoints Установить максимальное количество точке
	 * @param count Максимальное количество точке
	 */
    void setMaxPoints( int count );

	/**
	 * @brief clear Очистить кривую
	 */
    void clear();

	/**
	 * @brief clear Очистить кривую до указанного смещения
	 * @param left Смещение
	 */
    void clear(double left);

	/**
	 * @brief isGoingToLeft Проверка на выход за пределы влево от видимой области кривой
	 * @param x Смещение
	 * @return true если выходит за пределы, false если нет
	 */
    bool isGoingToLeft(double x) const;

	/**
	 * @brief left Получить смещение слева
	 * @return Смещение
	 */
    double left() const;

	/**
	 * @brief right Получить смещение справа
	 * @return Смешение
	 */
    double right() const;

	/**
	 * @brief getCurrentPos Получить текущую позицию
	 * @return Текущая позиция
	 */
    int getCurrentPos() const;

private:
	//! Данные кривой
	CurveData *_data = nullptr;
};
//----------------------------------------------------------------------------------
#endif //CURVE_H
//----------------------------------------------------------------------------------
