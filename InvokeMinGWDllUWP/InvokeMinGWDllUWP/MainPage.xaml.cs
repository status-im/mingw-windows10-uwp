using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Runtime.InteropServices;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace InvokeMinGWDllUWP
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            obtainedValueTextBlock.Text = String.Format("Loaded values from MinGW dll: {0} and {1}",
                GetConstantInt32FromDLL(), GetConstantInt64FromDLL());
        }

        [DllImport("PureMinGWDLL")]
        static extern int GetConstantInt32FromDLL();

        [DllImport("PureMinGWDLL")]
        static extern int GetConstantInt64FromDLL();
    }
}
