using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GarantEEG_Viewer
{
    public class FilterInfo
    {
        //! Тип фильтра
        public int Type { get; set; }

        //! Минимальная частота среза
        public int Frequency { get; set; }

        public FilterInfo()
        {
        }

        public FilterInfo(int type, int frequency)
        {
            Type = type;
            Frequency = frequency;
        }
    }
}
