//*****************************************************************************
//
// Имя файла    : 'wheel_controll.cpp'
// Заголовок    : Управление платформой
// Автор        : Барышников Р. А.
// Контакты     : plexus_bra@rambler.ru
// Дата         : 09.04.2013
//
//*****************************************************************************

#include "wheel_controll.h"
#include "gpio.h"

// =============================================================================
//                           Глобальные переменные
// =============================================================================

	int g_MDArray[5] = {MD_LEFT, MD_RIGHT, MD_KEY, MD_BACK, MD_FORWARD};

// ============================================================================
///    
///			                  Инициализация линий
///
// ============================================================================

void WCInit (void)
{
	for (int i = 0; i < 5; i++)
	{
		GPIOInit(g_MDArray[i]);
	}

	// Установка линии MD_KEY в "1". Эта линия предусмотрена
	// для управления скоростью. В нашем случае скоростью
	// не управляем, поэтому всегда должна стоять "1".
	GPIOSet(MD_KEY);
}

// ============================================================================
///    
///			                 Выполнение команды
///
// ============================================================================
/// \param	cmd  Команды:
///							FORWARD - движение вперед
///							STOP	- движение стоп
///							BACK  	- движение назад
///							LEFT 	- руль влево
///							RIGHT 	- руль вправо
///							CENTER 	- руль по центру
// ============================================================================

void WCCommand(ECommandWheel cmd)
{
	switch(cmd)
	{
		case FORWARD: 
		{
			GPIOClr(MD_BACK);
			GPIOSet(MD_FORWARD);
			break;
		}
		case STOP:
		{
			GPIOClr(MD_BACK);
			GPIOClr(MD_FORWARD);
			break;
		}
		case BACK:
		{
			GPIOClr(MD_FORWARD);
			GPIOSet(MD_BACK);
			break;
		}
		case LEFT:
		{
			GPIOClr(MD_RIGHT);
			GPIOSet(MD_LEFT);
			break;
		}
		case RIGHT:
		{
			GPIOClr(MD_LEFT);
			GPIOSet(MD_RIGHT);
			break;
		}
		case CENTER:
		{
			GPIOClr(MD_LEFT);
			GPIOClr(MD_RIGHT);
			break;
		}
	}
}