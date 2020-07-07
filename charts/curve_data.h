/**
@file curve_data.h

@brief Объявление класса для данных кривой графика

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef CURVE_DATA_H
#define CURVE_DATA_H
//----------------------------------------------------------------------------------
#include <qwt_series_data.h>
#include <vector>
//----------------------------------------------------------------------------------
//! Класс данных кривой графика
class CurveData : public QwtSeriesData<QPointF>
{
public:
	/**
	 * @brief CurveData Конструктор
	 */
    CurveData();

public:
	/**
	 * @brief sample Получить значение по смещению
	 * @param i Смещение
	 * @return Значение
	 */
    QPointF sample(size_t i) const override { return _data[i]; }

	/**
	 * @brief size Получить размер или текущий индекс
	 * @return Значение
	 */
    size_t size() const override { return _currentIndex<_data.size()? _currentIndex: _data.size(); }

	/**
	 * @brief boundingRect Получить видимую область данных кривой
	 * @return Видимая область
	 */
    QRectF boundingRect() const override { return d_boundingRect; }

	/**
	 * @brief setPointsCount Установить максимальное количество точек
	 * @param count Максимальное количество точек
	 */
    void setPointsCount( int count );

	/**
	 * @brief getCurrentPos Получить текущую позицию
	 * @return Текущая позиция
	 */
    const int getCurrentPos() const{ return _data.size()!=0 ? _currentIndex%_data.size() : _currentIndex; }

public:
	/**
	 * @brief appendValue Добавить значение
	 * @param value Значение
	 */
    void appendValue(double value);

	/**
	 * @brief clear Очистить данные кривой
	 */
    void clear();

	/**
	 * @brief clear Очистить данные кривой по смещению слева
	 * @param left Смещение слева
	 */
    void clear(double left);

private:
	/**
	 * @brief updateBoundingRect Обновить отображаемую область
	 * @param value Значение
	 */
    void updateBoundingRect(double value);

private:
	//! Текущий индекс
    int _currentIndex{0};

	//! Данные
    std::vector<QPointF> _data;
};
//----------------------------------------------------------------------------------
#endif //CURVE_DATA_H
//----------------------------------------------------------------------------------
