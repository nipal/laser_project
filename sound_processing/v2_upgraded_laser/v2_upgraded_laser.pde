import java.util.*;
import beads.*;
//import arduino.*;
import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

AudioContext ac;
float ff = 121f;
int nb_chan = 35; // oulala on commance a faire du sale avec les globale

// chan[9] init freq

// chan[10] note->0
// chan[33] note->23

class Caca {
  WavePlayer wp;
  Gain g;
  boolean  on;
  float    amp;
  float    freq;
  int      chan;

  Caca(int nb_chan) {
    wp = new WavePlayer(ac, 220f, Buffer.SINE);
    g = new Gain(ac, 1, new Envelope(ac, 0.1));
    g.addInput(wp);
    on = false;
    amp = 0;
    freq = 0;
    chan = nb_chan;
  }

  void setGain(float f) {
    amp = f;
    g.setGain(((on) ? amp : 0));
  }
  void setFrequency(float f) {
    wp.setFrequency(f);
    freq = f;
  }
  void  setStatment(boolean state)
  {
    on = state;
    g.setGain(((on) ? amp : 0));
//    println("amp:", amp);

//    println("statment:", state);
  }
  void  describe()
  {
    println("chan:", chan, "state:" , (on)? "on " : "off" , " freq:", freq, "  amp:", amp);
  }
  
  Gain getGain() {
    return g;
  }
}

ArrayList<Caca> cacaList = new ArrayList<Caca>();

//Arduino arduino;

void setup() {
//  arduino.list();
  size(300,300);
   ac = new AudioContext();

   for( int i = 0; i < nb_chan; i += 1) {
     Caca c = new Caca(i);

     cacaList.add(c);

     ac.out.addInput( c.getGain() );
     c.setGain(0);
   }

  for (Caca c : cacaList) {
  }
  ac.start();

  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1", 12000);
}

color fore = color(255, 102, 204);
color back = color(0,0,0);

void draw() {}

String  fstr_refacto(String str)
{
    String  refacto;
    int     id_coma;
    int     i;
    int     len;

    len = str.length();
    id_coma = -1;
    for (i = 0; i < len; i++)
    {
        if (str.charAt(i) == ',')                
            id_coma = i;
    }
    if (id_coma != -1)
        refacto = str.substring(0, id_coma) + "." + str.substring(id_coma + 1, len);
    else
        refacto = str;
    return (refacto);
}

float   osc_get_fval(OscMessage msg)
{
    char    type0;
    float   val;

    val = 0;
    type0 = msg.typetag().charAt(0);
  
    switch (type0)
    {
        case 'i': 
            val = float(msg.get(0).intValue());
            break;
        case 'f':
            val = msg.get(0).floatValue();
            break;
        case 's':
            val = float(fstr_refacto(msg.get(0).stringValue()));
            break;
    }
//    println("type:",  type0);
    
    return (val);
}

void    set_param_v1(OscMessage msg)
{
    String[]    ss = match( msg.addrPattern(), "/chan([0-9]+)/([A-z]+)");
    int         id_chan = int(ss[1]);
    String      param = ss[2];
    float       val = osc_get_fval(msg);

    switch (ss[2]) {
        case "amp":
          cacaList.get(int(ss[1])).setGain(val);
        break;
        case "freq":
          cacaList.get(int(ss[1])).setFrequency(val);
        break;
        case "on":
          cacaList.get(int(ss[1])).setStatment((int(val)==1));
        break;
    }


}

void    oscPrintValue(OscMessage msg)
{
    int         i, len;
    String      typetag;
    char        c;
    OscArgument arg;
    String      print_val;

    /* print the address pattern and the typetag of the received OscMessage */
    print("### received an osc message.");
    print("   addrpattern: "+msg.addrPattern());
    print("   typetag: "+msg.typetag());
    println("");

    typetag = msg.typetag();
    len = typetag.length();
    for (i = 0; i < len; i++)
    {
        c = typetag.charAt(i);
        arg = msg.get(i);
        switch(c)
        {
            case 'i': 
                print_val = str(arg.intValue());
                break ;
            case 'f': 
                print_val = str(arg.floatValue());
                break ;
            case 's': 
                print_val = arg.stringValue();
                break ;
            case 'b': 
                print_val = str(arg.booleanValue());
                break ;
            default :
                print_val = " unknown type ";
                break ;
        }
        println("   arg[", i, "]: ", c, "   ", print_val);
    }
}



void    set_param_v2(OscMessage msg)
{
    String[] ss = match( msg.addrPattern(), "/liss/([0-9]+)");

    
    println( msg.addrPattern(), "     note:", ss[0]);
    println( msg.addrPattern(), "     note:", ss[1]);

//    oscPrintValue(msg);

    // on veux jouer des note en fonction de truc cool
   
}

void    set_param_v3(OscMessage msg)
{
 //   oscPrintValue(msg);

    int note = msg.get(1).intValue() - 60;
    boolean st = (msg.get(2).floatValue() == 0) ? false : true;
    float   freq_init;

    println("note:", note, "    sate:", st);
    cacaList.get((note + 10)).setStatment(st);

//    cacaList.get(int(ss[1])).setGain(val);
//    cacaList.get(int(ss[1])).setFrequency(val);

    // on veux jouer des note en fonction de truc cool
   
}

void    set_piano_freq(int nb_note, float val)
{     
    float freq_val;
    int i;

    for (i = 0; i < nb_note;  i++)
    {
        freq_val = val * pow(1.059463094, i);
        println("       freq_val[", i, ":", freq_val);
        cacaList.get((i + 10)).setFrequency(freq_val);
    }
 
}
void    set_lissajoue_freq(int nb_note, float val)
{     
    float freq_val;
    int i, j;

     cacaList.get((10)).setFrequency(val);
     println("       freq_val[0]", val);
     for (i = 1; i <= nb_note;  i++)
     {
        j = 24 - i;

         freq_val = val * (float(j + 1) / float(j));
         println("       freq_val[", i, "]:", freq_val);
         cacaList.get((i + 10)).setFrequency(freq_val);
     }

}



// chan[10] note->0
// chan[33] note->23
void    set_param_piano(OscMessage msg)
{
    float   freq_val;
 //   oscPrintValue(msg);
    String[] ss = match( msg.addrPattern(), "/piano/([A-z]*)");
   // println("---------------------->", ss[1]);
    // on veux jouer des note en fonction de truc cool

   
    int i;
    int nb_note = 23;
    float val = osc_get_fval(msg);

    
    switch (ss[1])
    {
        case "freq":
            set_piano_freq(nb_note, val);
           // set_lissajoue_freq(nb_note, val);



//              println("-------");
//  //              for (i = 0; i < nb_note;  i++)
//  //              {
//  //                  freq_val = val * pow(1.059463094, i);
//  //                  println("       freq_val[", i, ":", freq_val);
//  //                  cacaList.get((i + 10)).setFrequency(freq_val);
//  //              }
//              
//              cacaList.get((10)).setFrequency(val);
//              println("       freq_val[0]", val);
//              for (i = 1; i <= nb_note;  i++)
//              {
//                  freq_val = val * (float(i + 1) / float(i));
//                  println("       freq_val[", i, "]:", freq_val);
//                  cacaList.get((i + 10)).setFrequency(freq_val);
//              }
            break ;
        case "amp":
            println("-------");
            for (i = 0; i <= nb_note;  i++)
            {
                cacaList.get((i + 10)).setGain(val);
            }
            break ;
        case "on":
             for (i = 0; i < nb_chan;  i++)
            {
                if (val == 0)
                    cacaList.get((i)).setStatment(false);
            }
            break ;
    }

    // freq:        --> fondamentale + le reste
    //  amp:        --> fondamentale + le reste
    //  on :        --> rien

    //  fondamentale --> 9
    //  le reste     --> 10, 33
   
}

void oscEvent(OscMessage msg) {
    String  tmp;

    tmp = msg.addrPattern().substring(0,5);
    
    println("tmp:", tmp);
    switch (tmp)
    {
        case "/chan":
            set_param_v1(msg);
            break;
        case "/liss":
            set_param_v2(msg);
            break;
        case "/note":
            set_param_v3(msg);
            break;
        case "/pian":
            set_param_piano(msg);
            break;

    }

 // String[] ss = match( msg.addrPattern(), "/chan([0-9]+)/([A-z]+)");
//  String val = match( msg.get(0).stringValue(), "([0-9]*),([0-9]*)")[1];

//   println("[0]", ss[0]);
//   println("[1]", ss[1]);
//    println("[2]", ss[2]);
//




    float val = osc_get_fval(msg);
    println("value ==> ", val);



//    println("[0]", ss[0], "[1]", ss[1], "[2]");
 // String val = match( msg.get(0).stringValue(), "([0-9]*),([0-9]*)")[1];

}

void    keyPressed()
{
    int i;

    if (key == ' ')
    {
        println("==========================================================");
        for (i = 0; i < nb_chan; i++)
        {
            if (cacaList.get(i).on)
                cacaList.get(i).describe();
        }  
    }
}

// pour tester les message
//void keyPressed() {
//  OscMessage t1 = new OscMessage("/test/int");
//  OscMessage t2 = new OscMessage("/test/float");
//  OscMessage t3 = new OscMessage("/test/string");
//
//  t1.add(1337);
//  t2.add(0.42);
//  t3.add("23,67");
//
//  oscP5.send(t1, myRemoteLocation); 
//  oscP5.send(t2, myRemoteLocation); 
//  oscP5.send(t3, myRemoteLocation); 
//
//}
