// QCodeEditor
#include <QLanguage>
#include <QFaustCompleter>

// Qt
#include <QFile>
#include <QStringListModel>

QFaustCompleter::QFaustCompleter(QObject *parent) : QCompleter(parent)
{
    // Setting up Faust types and functions
    QStringList list;

    Q_INIT_RESOURCE(qcodeeditor_resources);
    QFile fl(":/languages/faust.xml");

    if (!fl.open(QIODevice::ReadOnly))
    {
        // Fallback to hardcoded list if resource fails
        list << "process" << "declare" << "import" << "library" << "environment" << "component"
             << "with" << "letrec" << "where" << "case" << "waveform" << "soundfile" << "route"
             << "inputs" << "outputs" << "seq" << "par" << "sum" << "prod"
             << "button" << "checkbox" << "vslider" << "hslider" << "nentry" 
             << "vgroup" << "hgroup" << "tgroup" << "vbargraph" << "hbargraph"
             << "mem" << "prefix" << "int" << "float" << "rdtable" << "rwtable"
             << "select2" << "select3" << "ffunction" << "fconstant" << "fvariable"
             << "attach" << "lowest" << "highest"
             << "abs" << "acos" << "asin" << "atan" << "atan2" << "ceil" << "cos"
             << "exp" << "floor" << "fmod" << "log" << "log10" << "max" << "min"
             << "pow" << "remainder" << "rint" << "round" << "sin" << "sqrt" << "tan";
    }
    else
    {
        QLanguage language(&fl);

        if (language.isLoaded())
        {
            auto keys = language.keys();
            for (auto &&key : keys)
            {
                auto names = language.names(key);
                list.append(names);
            }
        }
    }

    // Add some common library functions and patterns
    list << "os.osc" << "os.sawtooth" << "os.triangle" << "os.square" << "os.phasor"
         << "no.noise" << "no.pink_noise" << "no.lfnoise" << "no.multirandom"
         << "fi.lowpass" << "fi.highpass" << "fi.bandpass" << "fi.notch" << "fi.peak_eq"
         << "fi.resonbp" << "fi.resonhp" << "fi.resonlp" << "fi.filterbank"
         << "de.delay" << "de.fdelay" << "de.sdelay" << "de.fdelayltv" << "de.echo"
         << "dm.zita_light" << "dm.freeverb_demo" << "dm.stereo_freeverb"
         << "ef.gate_mono" << "ef.gate_stereo" << "ef.compressor_mono" << "ef.limiter"
         << "ef.distortion1" << "ef.cubicnl" << "ef.gate_compressor"
         << "en.adsr" << "en.asr" << "en.ar" << "en.ahdshr" << "en.smoothEnvelope"
         << "ba.time" << "ba.samp2sec" << "ba.sec2samp" << "ba.db2linear" << "ba.linear2db"
         << "ba.selector" << "ba.selectn" << "ba.if" << "ba.bypass1" << "ba.bypass2"
         << "si.smoo" << "si.smooth" << "si.polysmooth" << "si.bus" << "si.block"
         << "ma.PI" << "ma.E" << "ma.SR" << "ma.T" << "ma.BS" << "ma.EPSILON"
         << "ro.cross" << "ro.interleave" << "ro.hadamard";

    setModel(new QStringListModel(list, this));
    setCompletionColumn(0);
    setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    setCaseSensitivity(Qt::CaseSensitive);
    setWrapAround(true);
}