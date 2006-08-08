/* rhino.c - driver for Microsol Rhino UPS hardware

   Copyright (C) 2004  Silvino B. Magalhães  <sbm2yk@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

   2004/11/13 - Version 0.10 - Initial release
   2005/07/07 - Version 0.20 - Initial rhino commands tests
   2005/10/25 - Version 0.30 - Operational-1 release
   2005/10/26 - Version 0.40 - Operational-2 release
   2005/11/29 - Version 0.50 - rhino commands release


   http://www.microsol.com.br

*/

#define DRV_VERSION "0.50"

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/ioctl.h>
#include "main.h"
#include "serial.h"
#include "rhino.h"

#define UPSDELAY 500 /* 0.5 ms delay */

/* comment on english language */
/* #define PORTUGUESE */

/* The following Portuguese strings are in UTF-8. */
#ifdef PORTUGUESE
#define M_UNKN     "Modêlo rhino desconhecido\n"
#define NO_RHINO   "Rhino não detectado! abortando ...\n"
#define UPS_DATE   "Data no UPS %4d/%02d/%02d\n"
#define SYS_DATE   "Data do Sistema %4d/%02d/%02d dia da semana %s\n"
#define ERR_PACK   "Pacote errado\n"
#define NO_EVENT   "Não há eventos\n"
#define UPS_TIME   "Hora interna UPS %0d:%02d:%02d\n"
#else
#define M_UNKN     "Unknown rhino model\n"
#define NO_RHINO   "Rhino not detected! aborting ...\n"
#define UPS_DATE   "UPS Date %4d/%02d/%02d\n"
#define SYS_DATE   "System Date %4d/%02d/%02d day of week %s\n"
#define ERR_PACK   "Wrong package\n"
#define NO_EVENT   "No events\n"
#define UPS_TIME   "UPS internal Time %0d:%02d:%02d\n"
#endif

int rhino_cmd = 0;

static int
AutonomyCalc( int ia ) /* all models */
{

  int result = 0;
  double  auton, calc, currin;

  if( ia )
    {
      if( ( BattVoltage == 0 ) )
	result = 0;
      else
	{
	  calc = ( OutVoltage * OutCurrent )* 1.0 / ( 0.08 * BattVoltage );
	  auton = pow( calc, 1.18 );
	  if(  ( auton == 0 ) )
	    result = 0;
	  else
	    {
	      auton = 1.0 / auton;
	      auton = auton * 11.07;
	      calc = ( BattVoltage * 1.0 / 10 ) - 168;
	      result = (int) ( auton * calc * 2.5 );
	    }
	}
    }
  else
    {
      currin = ( UtilPowerOut + ConstInt ) *1.0 / Vin;
      auton = ( ( ( AmpH *1.0 / currin ) * 60 * ( ( BattVoltage - VbatMin ) * 1.0 /( VbatNom - VbatMin ) ) * FM ) + FA );
      if(  ( BattVoltage > 129 ) || ( BattVoltage < 144 ) )
	result = 133;
      else
	result = (int) auton;
    }

  return result;

}

/* Treat received package */
static void
ScanReceivePack( void )
{

  /* model independent data */

  Year = RecPack[31] + ( RecPack[32] * 100 );
  Month = RecPack[30];
  Day = RecPack[29];

  /* UPS internal time */
  ihour = RecPack[26];
  imin  = RecPack[27];
  isec  = RecPack[28];

  /* Flag1 */
  /* SobreTemp        = ( ( 0x01 & RecPack[33]) = 0x01 ); */
  /* OutputOn         = ( ( 0x02 & RecPack[33]) = 0x02 ); OutputOn */
  /* InputOn          = ( ( 0x04 & RecPack[33]) = 0x04 ); InputOn */
  /* ByPassOn         = ( ( 0x08 & RecPack[33]) = 0x08 ); BypassOn */
  /* Auto_HAB         = ( ( 0x10 & RecPack[33]) = 0x10 ); */
  /* Timer_HAB        = ( ( 0x20 & RecPack[33]) = 0x20 ); */
  /* Boost_Ligado     = ( ( 0x40 & RecPack[33]) = 0x40 ); */
  /* Bateria_Desc     = ( ( 0x80 & RecPack[33]) = 0x80 ); */

  /* Flag2 */
  /* Quad_Ant_Ent     = ( ( 0x01 & RecPack[34]) = 0x01 ); */
  /* Quadratura       = ( ( 0x02 & RecPack[34]) = 0x02 ); */
  /* Termino_XMODEM   = ( ( 0x04 & RecPack[34]) = 0x04 ); */
  /* Em_Sincronismo   = ( ( 0x08 & RecPack[34]) = 0x08 ); */
  /* Out110           = ( ( 0x10 & RecPack[34]) = 0x10 ); Out110 */
  /* Exec_Beep        = ( ( 0x20 & RecPack[34]) = 0x20 ); */
  /* LowBatt          = ( ( 0x40 & RecPack[34]) = 0x40 ); LowBatt */
  /* Boost_Sobre      = ( ( 0x80 & RecPack[34]) = 0x80 ); */

  /* Flag3 */
  /* OverCharge       = ( ( 0x01 & RecPack[35]) = 0x01 ); OverCharge */
  /* SourceFail       = ( ( 0x02 & RecPack[35]) = 0x02 ); SourceFail */
  /* RedeAnterior     = ( ( 0x04 & RecPack[35]) = 0x04 ); */
  /* Cmd_Executado    = ( ( 0x08 & RecPack[35]) = 0x08 ); */
  /* Exec_Autoteste   = ( ( 0x10 & RecPack[35]) = 0x10 ); */
  /* Quad_Ant_Sai     = ( ( 0x20 & RecPack[35]) = 0x20 ); */
  /* ComandoSerial    = ( ( 0x40 & RecPack[35]) = 0x40 ); */
  /* SobreTensao      = ( ( 0x80 & RecPack[35]) = 0x80 ); */

  OutputOn = ( ( 0x02  & RecPack[33] ) == 0x02 );
  InputOn = ( ( 0x04  & RecPack[33] ) == 0x04 );
  BypassOn = ( ( 0x08  & RecPack[33] ) == 0x08 );

  Out110 = ( ( 0x10  & RecPack[34] ) == 0x10 );
  LowBatt = ( ( 0x40  & RecPack[34] ) == 0x40 );

  OverCharge = ( ( 0x01 & RecPack[35] ) == 0x01 );
  SourceFail = ( ( 0x02  & RecPack[35] ) == 0x02 );

  /* model dependent data read */
  
  PowerFactor = 800;
  
  if(  RecPack[0] ==0xC2 )
    {
      LimInfBattSrc = 174;
      LimSupBattSrc = 192;//180????? carregador eh 180 (SCOPOS)
      LimInfBattInv = 174;
      LimSupBattInv = 192;//170????? (SCOPOS)
    }
  else
    {
      LimInfBattSrc = 138;
      LimSupBattSrc = 162;//180????? carregador eh 180 (SCOPOS)
      LimInfBattInv = 126;
      LimSupBattInv = 156;//170????? (SCOPOS)
    }
  
  BattNonValue = 144;
  /*  VersaoInterna = "R10" + IntToStr( RecPack[1] ); */
  InVoltage = RecPack[2];
  InCurrent = RecPack[3];
  UtilPowerIn = RecPack[4] + RecPack[5] * 256;
  AppPowerIn = RecPack[6] + RecPack[7] * 256;
  FatorPotEntrada = RecPack[8];
  InFreq = ( RecPack[9] + RecPack[10] * 256 ) * 1.0 / 10;
  OutVoltage = RecPack[11];
  OutCurrent = RecPack[12];
  UtilPowerOut = RecPack[13] + RecPack[14] * 256;
  AppPowerOut = RecPack[15] + RecPack[16] * 256;
  FatorPotSaida = RecPack[17];
  OutFreq = ( RecPack[18] + RecPack[19] * 256 ) * 1.0 / 10;
  BattVoltage = RecPack[20];
  BoostVolt = RecPack[21] + RecPack[22] * 256;
  Temperature = ( 0x7F & RecPack[23] );
  Rendimento = RecPack[24];

  /* model independent data */
  
  if(  ( BattVoltage < LimInfBattInv ) )
    CriticBatt = true;
  
  if(  BypassOn )
    OutVoltage = ( InVoltage * 1.0 / 2 ) + 5;
  
  if(  SourceFail && RedeAnterior ) // falha pela primeira vez
    OcorrenciaDeFalha = true;
  
  if(  !( SourceFail ) && !( RedeAnterior ) ) // retorno da rede
    RetornoDaRede = true;
  
  if( !( SourceFail ) == RedeAnterior )
    {
      RetornoDaRede = false;
      OcorrenciaDeFalha = false;
    }
  
  RedeAnterior = !( SourceFail );
  
  LimInfSaida = 75;
  LimSupSaida = 150;
  ValorNominalSaida = 110;
  
  LimInfEntrada = 190;
  LimSupEntrada = 250;
  ValorNominalEntrada = 220;
  
  if(  SourceFail )
    {
      StatusEntrada = 2;
      RecPack[8] = 200; /* ?????????????????????????????????? */
    }
  else
    {
      StatusEntrada = 1;
      RecPack[8] = 99; /* ??????????????????????????????????? */
    }
  
  if(  OutputOn )     // Output Status
    StatusSaida = 2;
  else
    StatusSaida = 1;
  
  if(  OverCharge )
    StatusSaida = 3;
  
  if(  CriticBatt ) // Battery Status
    StatusBateria = 4;
  else
    StatusBateria = 1;
  
  EventosRede = 0;
  
  if(  OcorrenciaDeFalha )
    EventosRede = 1;
  
  if(  RetornoDaRede )
    EventosRede = 2;
  
  /* verify InversorOn */
  if(  Flag_inversor )
    {
      oldInversorOn = InputOn;
      Flag_inversor = false;
    }

  EventosSaida = 0;
  if(  InputOn && !( oldInversorOn ) )
    EventosSaida = 26;
  if(  oldInversorOn && !( InputOn ) )
    EventosSaida = 27;
  oldInversorOn = InputOn;
  if(  SuperAquecimento && !( SuperAquecimentoAnterior ) )
    EventosSaida = 12;
  if(  SuperAquecimentoAnterior && !( SuperAquecimento ) )
    EventosSaida = 13;
  SuperAquecimentoAnterior = SuperAquecimento;
  EventosBateria = 0;
  OldCritBatt = CriticBatt;

  if(  OverCharge && !( OldOverCharge ) )
    EventosSaida = 10;
  if(  OldOverCharge && !( OverCharge ) )
    EventosSaida = 11;
  OldOverCharge = OverCharge;

  /* autonomy calc. */
  if(  RecPack[ 0 ] ==0xC2  )
    Autonomy = AutonomyCalc( 1 );
  else
    Autonomy = AutonomyCalc( 0 );

}

static void
CommReceive(const char *bufptr,  int size)
{

  int i, i_end, CheckSum, chk;
  
  if(  ( size==37 ) )
    Waiting = 0;
  
  printf("CommReceive size = %d waiting = %d\n", size, Waiting );

  switch( Waiting )
    {
      /* normal package */
    case 0:
      {
	if(  size == 37 )
	  {
	    i_end = 37;
	    for( i = 0 ; i < i_end ; ++i )
	      {
		RecPack[i] = *bufptr;
		bufptr++;
	      }
	    
	    /* CheckSum verify */
	    CheckSum = 0;
	    i_end = 36;
	    for( i = 0 ; i < i_end ; ++i )
	      {
		chk =  RecPack[ i ];
		CheckSum = CheckSum + chk;
	      }

	    CheckSum = CheckSum % 256;

	    ser_flush_in(upsfd,"",0); /* clean port */

	    /* correct package */
	    if(  ( RecPack[0] == 0xC0 || RecPack[0] == 0xC1 || RecPack[0] == 0xC2 || RecPack[0] == 0xC3 )
		  && ( RecPack[ 36 ] == CheckSum ) )
	       {

		 if(!(detected))
		   {
		     RhinoModel = RecPack[0];
		     detected = true;
		   }

		 switch( RhinoModel )
		   {
		   case 0xC0:
		   case 0xC1:
		   case 0xC2:
		   case 0xC3:
		     {
		       ScanReceivePack();
		       break;
		     }
		   default:
		     {
		       printf( M_UNKN );
		       break;
		     }
		   }
	       }

           }
	
	 break;
       }
       
     case 1:
       {
	 /* dumping package, nothing to do yet */
	 Waiting = 0;
	 break;
       }

    }

   Waiting =0;

}

static int
send_command( int cmd )
{

  int i, chk, checksum=0, iend=18, sizes, ret, kount; /*, j, uc; */
  unsigned char ch, psend[19];
  sizes = 19;
  checksum = 0;
  
  /* mounting buffer to send */

  for(i = 0; i < iend; i++ )
    {
      if ( i == 0 )
	chk = 0x01;
      else
	{
	  if( i == 1)
	    chk = cmd;
	  else
	    chk = 0x00; // 0x20;
	}

      ch = chk;
      psend[i] = ch; /* psend[0 - 17] */
      if( i > 0 )  /* psend[0] not computed */
	checksum = checksum + chk;
    }

  ch = checksum;
  ch = (~( ch) ); /* not ch  */
  psend[iend] = ch;

  /* send five times the command */
  kount = 0;
  while ( kount < 5 )
    {
      /* ret = ser_send_buf_pace(upsfd, UPSDELAY, psend, sizes );// optional delay */
      
      for(i=0; i < 19; i++)
	{
	  ret = ser_send_char( upsfd, psend[i] );
	  /* usleep ( UPSDELAY ); sending without delay */
	}
      
      usleep( UPSDELAY ); /* delay between sent command */

      kount++;
    }


  return ret;

}

static void sendshut( void )
{

	int i;

	for(i=0; i < 30000; i++)
	  usleep( UPSDELAY ); /* 15 seconds delay */

	send_command( CMD_SHUT );
	upslogx(LOG_NOTICE, "Ups shutdown command sent");
	printf("Ups shutdown command sent\n");

}

static void getbaseinfo(void)
{
	unsigned char  temp[256];
	unsigned char Pacote[37];
	int  tam, i, j=0;
	time_t *tmt;
	struct tm *now;
	tmt  = ( time_t * ) malloc( sizeof( time_t ) );
	time( tmt );
	now = localtime( tmt );
	dian = now->tm_mday;
	mesn = now->tm_mon+1;
	anon = now->tm_year+1900;
        weekn = now->tm_wday;

	/* trying detect rhino model */
	while ( ( !detected ) && ( j < 10 ) )
	  {

	    temp[0] = 0; // flush temp buffer
	    tam = ser_get_buf_len(upsfd, temp, pacsize, 3, 0);
	    if( tam == 37 )
	      {
		for( i = 0 ; i < tam ; i++ )
		  {
		    Pacote[i] = temp[i];
		  }
	      }

	    j++;
	    if( tam == 37)
	      CommReceive(Pacote, tam);
	     else
	      CommReceive(temp, tam);
	  }

	if( (!detected) )
	  {
	    printf( NO_RHINO );
	    upsdrv_cleanup();
	    exit(0);
	  }

	switch( RhinoModel )
	  {
	  case 0xC0:
	    {
	      strcpy(Model, "Rhino 20.0 kVA");
	      PotenciaNominal = 20000;
	      break;
	    }
	  case 0xC1:
	    {
	      strcpy(Model, "Rhino 10.0 kVA");
	      PotenciaNominal = 10000;
	      break;
	    }
	  case 0xC2:
	    {
	      strcpy(Model, "Rhino 6.0 kVA");
	      PotenciaNominal = 6000;
	      break;
	    }
	  case 0xC3:
	    {
	     strcpy(Model, "Rhino 7.5 kVA");
	      PotenciaNominal = 7500;
	      break;
	    }
	  }

	/* manufacturer and model */
	dstate_setinfo("ups.mfr", "%s", "Microsol");
	dstate_setinfo("ups.model", "%s", Model);
	/*
	dstate_setinfo("input.transfer.low", "%03.1f", InDownLim); LimInfBattInv ?
	dstate_setinfo("input.transfer.high", "%03.1f", InUpLim); LimSupBattInv ?
	*/

	dstate_addcmd("shutdown.stayoff");	// CMD_SHUT
	/* there is no reserved words for CMD_INON and CMD_INOFF yet */
	/* dstate_addcmd("input.on");	// CMD_INON    = 1 */
	/* dstate_addcmd("input.off");	// CMD_INOFF   = 2 */
	dstate_addcmd("load.on");	/* CMD_OUTON   = 3 */
	dstate_addcmd("load.off");	/* CMD_OUTOFF  = 4 */
	dstate_addcmd("bypass.start");	/* CMD_PASSON  = 5 */
	dstate_addcmd("bypass.stop");	/* CMD_PASSOFF = 6 */

	printf("Detected %s on %s\n", dstate_getinfo("ups.model"), device_path);

}

static void getupdateinfo(void)
{
	unsigned char  temp[256];
	int tam, ret = 0;

        int hours, mins;
 
        /* time update */
        time_t *tmt;
        struct tm *now;
        tmt  = ( time_t * ) malloc( sizeof( time_t ) );
        time( tmt );
        now = localtime( tmt );
        hours = now->tm_hour;
        mins = now->tm_min;

	temp[0] = 0; /* flush temp buffer */
	tam = ser_get_buf_len(upsfd, temp, pacsize, 3, 0);

	CommReceive(temp, tam);

}

static int instcmd(const char *cmdname, const char *extra)
{

	int ret = 0;
	
	if (!strcasecmp(cmdname, "shutdown.stayoff"))
	  {
	    // shutdown now (one way)
	    /* send_command( CMD_SHUT ); */
	    sendshut();
	    return STAT_INSTCMD_HANDLED;
	  }

	if (!strcasecmp(cmdname, "load.on"))
	  {
	    // liga Saida
	    ret = send_command( 3 );
	    if ( ret < 1 )
	      upslogx(LOG_ERR, "send_command 3 failed");
	    return STAT_INSTCMD_HANDLED;
	  }

	if (!strcasecmp(cmdname, "load.off"))
	  {
	    // desliga Saida
	    ret = send_command( 4 );
	    if ( ret < 1 )
	      upslogx(LOG_ERR, "send_command 4 failed");
	    return STAT_INSTCMD_HANDLED;
	  }

	if (!strcasecmp(cmdname, "bypass.start"))
	  {
	    // liga Bypass
	    ret = send_command( 5 );
	    if ( ret < 1 )
	      upslogx(LOG_ERR, "send_command 5 failed");
	    return STAT_INSTCMD_HANDLED;
	  }

	if (!strcasecmp(cmdname, "bypass.stop"))
	  {
	    // desliga Bypass
	    ret = send_command( 6 );
	    if ( ret < 1 )
	      upslogx(LOG_ERR, "send_command 6 failed");
	    return STAT_INSTCMD_HANDLED;
	  }


	upslogx(LOG_NOTICE, "instcmd: unknown command [%s]", cmdname);
	return STAT_INSTCMD_UNKNOWN;

}

void upsdrv_initinfo(void)
{
	getbaseinfo();

	upsh.instcmd = instcmd;
	dstate_setinfo("driver.version.internal", "%s", DRV_VERSION);
}

void upsdrv_updateinfo(void)
{

        getupdateinfo(); /* new package for updates */

	dstate_setinfo("output.voltage", "%03.1f", OutVoltage);
	dstate_setinfo("input.voltage", "%03.1f", InVoltage);
	dstate_setinfo("battery.voltage", "%02.1f", BattVoltage);

	/* output and bypass tests */
	if( OutputOn )
	  dstate_setinfo("outlet.0.switchable", "%s", "Yes");
	else
	  dstate_setinfo("outlet.0.switchable", "%s", "No");

	if( BypassOn )
	  dstate_setinfo("outlet.1.switchable", "%s", "Yes");
	else
	  dstate_setinfo("outlet.1.switchable", "%s", "No");

	status_init();

	if (!SourceFail )
	  status_set("OL");		/* on line */
	else
	  status_set("OB");		/* on battery */
	
	if (Autonomy < 5 )
	  status_set("LB");		/* low battery */
	
	status_commit();
	dstate_setinfo("ups.temperature", "%2.2f", Temperature);
	dstate_setinfo("input.frequency", "%2.1f", InFreq);
	dstate_dataok();

}

/* power down the attached load immediately */
void upsdrv_shutdown(void)
{

	/* basic idea: find out line status and send appropriate command */
	/* on line: send normal shutdown, ups will return by itself on utility */
	/* on battery: send shutdown+return, ups will cycle and return soon */

	if (!SourceFail)     // on line
	  {
	    printf("On line, forcing shutdown command...\n");
	    send_command( CMD_SHUT );
	  }
	else
	  {
	    printf("On battery, sending normal shutdown command...\n");
	    send_command( CMD_SHUT );
	  }
	
}

void upsdrv_help(void)
{
}

void upsdrv_makevartable(void)
{
	
	addvar(VAR_VALUE, "battext", "Battery Extension (0-80)min");

}

void upsdrv_banner(void)
{
	printf("Network UPS Tools - Microsol Rhino UPS driver %s (%s)\n", 
		DRV_VERSION, UPS_VERSION);
        printf("by Silvino B. Magalhaes for Microsol - sbm2yk@gmail.com\n\n");
}

void upsdrv_initups(void)
{
	int     dtr_bit = TIOCM_DTR;
        int     rts_bit = TIOCM_RTS;

	upsfd = ser_open(device_path);
	ser_set_speed(upsfd, device_path, B19200);

	/* dtr and rts setting */
	ioctl(upsfd, TIOCMBIS, &dtr_bit);
	ioctl(upsfd, TIOCMBIC, &rts_bit);
	
}

void upsdrv_cleanup(void)
{
	ser_close(upsfd, device_path);
}

void upsdrv_print_ups_list(void)
{
	printf("List of supported UPSs\n");
	printf("===\n");
}
