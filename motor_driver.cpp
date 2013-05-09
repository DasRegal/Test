//*****************************************************************************
//
// Имя файла    : 'motor_driver.cpp'
// Заголовок    : Драйвер двигателей
// Автор        : Барышников Р. А.
// Контакты     : plexus_bra@rambler.ru
// Дата         : 09.04.2013
//
//*****************************************************************************

#include "motor_driver.h"
#include "gpio.h"

// =============================================================================
//                           Глобальные переменные
// =============================================================================

	CMotorDriver	mDriver;
	int g_MDArray[5] = {MD_LEFT, MD_RIGHT, MD_KEY, MD_BACK, MD_FORWARD};

// =============================================================================
///
///                             Класс CMotorDriver
///
// =============================================================================

// =============================================================================
///
///                            Конструктор класса
///
// =============================================================================

CMotorDriver::CMotorDriver()
{

}

// =============================================================================
///
///		                            Инициализация
///
// =============================================================================

void CMotorDriver::Init(void)
{
	FILE* fp;
	char gpioFileName[256];

	fp = NULL;

	int i;
	// Запись в файл export номеров gpio
	for (i = 0; i < 5; i++)
	{
		if ((fp = fopen("/sys/class/gpio/export", "ab")) != NULL)
		{
			rewind(fp);
			fprintf(fp, "%d", g_MDArray[i]);
			fclose(fp);

			//printf("gpio%d exported\n", g_MDArray[i]);
		}
		else
		{
			//printf("Error exported gpio%d\n", g_MDArray[i]);
		}
	}

	// Конфигурация gpio№ как OUT...
	for (i = 0; i < 5; i++)
	{
		sprintf(gpioFileName, "/sys/class/gpio/gpio%d/direction", g_MDArray[i]);
		if ((fp = fopen(gpioFileName, "rb+")) != NULL)
		{
			rewind(fp);
			fprintf(fp, "out");
			fclose(fp);

			printf("gpio%d configured for OUTPUT... ", g_MDArray[i]);
			
			// ... и установка линий в "0"
			sprintf(gpioFileName, "/sys/class/gpio/gpio%d/value", g_MDArray[i]);
			if ((fp = fopen(gpioFileName, "rb+")) != NULL)
			{
				fprintf(fp, "0");
				fclose(fp);
				//printf("Value set to \"0\"\n");
			}
			else
			{
				//printf("Error value\n");
			}
		}
		else
		{
			//printf("Error configured gpio%d\n", g_MDArray[i]);
		}
	}

	// Установка линии MD_KEY в "1". Эта линия предусмотрена
	// для управления скоростью. В нашем случае скоростью
	// не управляем, поэтому всегда должна стоять "1".
	mDriver.SetGPIO(MD_KEY);
}

// =============================================================================
///
///		                    Установка линии в "1"
///
// =============================================================================
///	\param   gpio  Номер линии
/// \return 	   Возвращение 1, если ошибка.
// =============================================================================

int CMotorDriver::SetGPIO (int gpio)
{
	FILE* fp;
	fp = NULL;
	char gpioFileName[256];

	sprintf(gpioFileName, "/sys/class/gpio/gpio%d/value", gpio);
	if ((fp = fopen(gpioFileName, "rb+")) != NULL)
	{
		rewind(fp);
		fprintf(fp, "1");
		fclose(fp);
		return 0;
	}
	else return 1;
}

// =============================================================================
///
///		                    Установка линии в "0"
///
// =============================================================================
///	\param   gpio  Номер линии
/// \return 	   Возвращение 1, если ошибка.
// =============================================================================

int CMotorDriver::ClrGPIO (int gpio)
{
	FILE* fp;
	fp = NULL;
	char gpioFileName[256];

	sprintf(gpioFileName, "/sys/class/gpio/gpio%d/value", gpio);
	if ((fp = fopen(gpioFileName, "rb+")) != NULL)
	{
		rewind(fp);
		fprintf(fp, "0");
		fclose(fp);
		return 0;
	}
	else return 1;
}

// =============================================================================
///
///		                    Инвертирование линии
///
// =============================================================================
///	\param   gpio  Номер линии
/// \return 	   Возвращение 1, если ошибка.
// =============================================================================

int CMotorDriver::InvGPIO (int gpio)
{
	FILE* fp;
	int state;
	char gpioFileName[256];
	fp = NULL;
	
	sprintf(gpioFileName, "/sys/class/gpio/gpio%d/value", gpio);
	if ((fp = fopen(gpioFileName, "rb+")) != NULL)
	{
		state = fgetc(fp);
		rewind(fp);
		if (state == '0')
		{
			fprintf(fp, "1");
		}
		else
		{
			fprintf(fp, "0");
		}
		fclose(fp);
		return 0;
	}
	else return 1;
}