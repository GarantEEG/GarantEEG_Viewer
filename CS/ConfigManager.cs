using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using TinyJson;

namespace GarantEEG_Viewer
{
    public class ConfigManager
    {
        public static ConfigManager Config { get; set; }

        public ConfigManager()
        {
            ResetValues();
        }

        //! Настройки для конфигурации по умолчанию
        public static string CONFIG_DEFAULT_VALUE_ip { get; } = "192.168.127.125";
        public static int CONFIG_DEFAULT_VALUE_port { get; } = 12345;
        public static bool CONFIG_DEFAULT_VALUE_autoreconnect { get; } = true;
        public static int CONFIG_DEFAULT_VALUE_displaySeconds { get; } = 5;
        public static int[] CONFIG_DEFAULT_VALUE_curveColors { get; } = new int[8]
        {
            Color.FromArgb(255, 0, 0).ToArgb(), //"#FF0000", //Qt::red
	        Color.FromArgb(0, 0, 0).ToArgb(), //"#000000", //Qt::black
	        Color.FromArgb(128, 128, 128).ToArgb(), //"#808080", //Qt::darkGray
	        Color.FromArgb(0, 255, 0).ToArgb(), //"#00FF00", //Qt::green
	        Color.FromArgb(0, 0, 255).ToArgb(), //"#0000FF", //Qt::blue
	        Color.FromArgb(255, 0, 255).ToArgb(), //"#FF00FF", //Qt::magenta
	        Color.FromArgb(255, 255, 0).ToArgb(), //"#FFFF00", //Qt::yellow
	        Color.FromArgb(128, 128, 0).ToArgb(), //"#808000" //Qt::darkYellow
        };
        public static bool CONFIG_DEFAULT_VALUE_useFilters { get; } = true;



        //! ИД для подключения к ЭЭГ
        public string IP { get; set; } = CONFIG_DEFAULT_VALUE_ip;

        //! Порт для подключения к ЭЭГ
        public int Port { get; set; } = CONFIG_DEFAULT_VALUE_port;

        //! Флаг автопереподключения к устройству при потере соединения
        public bool Autoreconnect { get; set; } = CONFIG_DEFAULT_VALUE_autoreconnect;

        //! Количество отображаемых секунд на графике
        public int DisplaySeconds { get; set; } = CONFIG_DEFAULT_VALUE_displaySeconds;

        //! Цвета для графиков ЭЭГ
        public int[] CurveColors { get; set;  } = new int[8]
        {
            CONFIG_DEFAULT_VALUE_curveColors[0],
            CONFIG_DEFAULT_VALUE_curveColors[1],
            CONFIG_DEFAULT_VALUE_curveColors[2],
            CONFIG_DEFAULT_VALUE_curveColors[3],
            CONFIG_DEFAULT_VALUE_curveColors[4],
            CONFIG_DEFAULT_VALUE_curveColors[5],
            CONFIG_DEFAULT_VALUE_curveColors[6],
            CONFIG_DEFAULT_VALUE_curveColors[7]
        };

        //! Состояние выбора для графиков ЭЭГ
        public bool[] CurveIsChecked { get; set; } = new bool[8]
        {
            true, true, true, true,
            true, true, true, true
        };

        //! Флаг необходимости использования фильтров
        public bool UseFilters { get; set; } = CONFIG_DEFAULT_VALUE_useFilters;

        //! Список фильтров
        public List<FilterInfo> Filters { get; set; } = new List<FilterInfo>();

        /**
         * @brief ResetValues Сброс значений
         */
        public void ResetValues()
        {
            IP = CONFIG_DEFAULT_VALUE_ip;
            Port = CONFIG_DEFAULT_VALUE_port;
            Autoreconnect = CONFIG_DEFAULT_VALUE_autoreconnect;
            DisplaySeconds = CONFIG_DEFAULT_VALUE_displaySeconds;

            for (int i = 0; i < 8; i++)
            {
                CurveColors[i] = CONFIG_DEFAULT_VALUE_curveColors[i];
                CurveIsChecked[i] = true;
            }

            UseFilters = CONFIG_DEFAULT_VALUE_useFilters;
            Filters.Clear();
        }

        /**
         * @brief Load Загрузить конфигурацию
         */
        public static ConfigManager Load(string path)
        {
            if (File.Exists(path))
                return File.ReadAllText(path).Decode<ConfigManager>();

            return new ConfigManager();
        }

        /**
         * @brief Save Сохранить конфигурацию
         */
        public void Save(string path)
        {
            File.WriteAllText(path, this.Encode(true));
        }
    }
}
