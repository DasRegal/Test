//*****************************************************************************
//
// Имя файла    : 'cd74ac153.h'
// Заголовок    : Драйвер мультиплексора CD74AC153
// Автор        : Барышников Р. А.
// Контакты     : plexus_bra@rambler.ru
// Дата         : 24.04.2013
//
//*****************************************************************************

#ifndef _CD74AC153_H
#define _CD74AC153_H

// =============================================================================
//                                Костанты
// =============================================================================

	// Номера линий gpio
	// Для ODROID-X,  35
	#define INPUT_A		97
	// Для ODROID-X, 27
	#define INPUT_B		88

// =============================================================================
//                             Типы/Структуры
// =============================================================================

	enum ESwLine
	{
		LINE1 = 0,
		LINE2 = 1,
		LINE3 = 2,
		LINE4 = 3
	};


// =============================================================================
//                                Классы
// =============================================================================

class CCD74
{
	public:
		// Конструктор класса
		CCD74();
		// Инициализация
		void Init 		(void);
		// Переключение лмнмм
		void SwitchLine (ESwLine line);
};

// =============================================================================
//                          Внешние зависимости
// =============================================================================

	extern	CCD74	cd74ac;

#endif // _CD74AC153_H