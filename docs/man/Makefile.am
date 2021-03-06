# Network UPS Tools: man
#

# Notes:
# - sources (.txt) and groff formats are both distributed,
# - only sources are versioned ; groff files are generated at worst
#   during 'make dist'
# - HTML files are built upon request, if AsciiDoc is available,
# - groff update will only happen if AsciiDoc is available too,
# - all this can probably (and hopefully) be improved, but I've not
#   found a way to do pattern replacement on the fly for target deps!
#   FIXME: investigate an autogen.sh hook
# - Ref: http://www.gnu.org/software/hello/manual/automake/Man-pages.html

# Base configuration and client manpages, always installed
SRC_CONF_PAGES = \
	nut.conf.txt \
	ups.conf.txt \
	upsd.conf.txt \
	upsd.users.txt \
	upsmon.conf.txt \
	upssched.conf.txt

MAN_CONF_PAGES = \
	nut.conf.5 \
	ups.conf.5 \
	upsd.conf.5 \
	upsd.users.5 \
	upsmon.conf.5 \
	upssched.conf.5

man5_MANS = $(MAN_CONF_PAGES)

HTML_CONF_MANS = \
	nut.conf.html \
	ups.conf.html \
	upsd.conf.html \
	upsd.users.html \
	upsmon.conf.html \
	upssched.conf.html

SRC_CLIENT_PAGES = \
	nutupsdrv.txt \
	upsc.txt \
	upscmd.txt \
	upsd.txt \
	upsdrvctl.txt \
	upslog.txt \
	upsmon.txt \
	upsrw.txt \
	upssched.txt

MAN_CLIENT_PAGES = \
	nutupsdrv.8 \
	upsc.8 \
	upscmd.8 \
	upsd.8 \
	upsdrvctl.8 \
	upslog.8 \
	upsmon.8 \
	upsrw.8 \
	upssched.8

man8_MANS = $(MAN_CLIENT_PAGES)

HTML_CLIENT_MANS = \
	nutupsdrv.html \
	upsc.html \
	upscmd.html \
	upsd.html \
	upsdrvctl.html \
	upslog.html \
	upsmon.html \
	upsrw.html \
	upssched.html

SRC_TOOL_PAGES = nut-scanner.txt nut-recorder.txt

MAN_TOOL_PAGES = nut-scanner.8 nut-recorder.8

man8_MANS += $(MAN_TOOL_PAGES)

HTML_TOOL_MANS = nut-scanner.html nut-recorder.html

# CGI (--with-cgi) related manpages
SRC_CGI_PAGES = \
	hosts.conf.txt \
	upsset.conf.txt \
	upsstats.html.txt \
	upsset.cgi.txt \
	upsstats.cgi.txt \
	upsimage.cgi.txt

MAN5_CGI_PAGES = \
	hosts.conf.5 \
	upsset.conf.5 \
	upsstats.html.5

MAN8_CGI_PAGES = \
	upsset.cgi.8 \
	upsstats.cgi.8 \
	upsimage.cgi.8

if WITH_CGI
 man5_MANS += $(MAN5_CGI_PAGES)

 man8_MANS += $(MAN8_CGI_PAGES)
endif

HTML_CGI_MANS = \
	hosts.conf.html \
	upsset.conf.html \
	upsstats.html.html \
	upsset.cgi.html \
	upsstats.cgi.html \
	upsimage.cgi.html


# Development (--with-dev) related manpages
SRC_DEV_PAGES = \
	upsclient.txt \
	upscli_connect.txt \
	upscli_disconnect.txt \
	upscli_fd.txt \
	upscli_get.txt \
	upscli_list_next.txt \
	upscli_list_start.txt \
	upscli_readline.txt \
	upscli_sendline.txt \
	upscli_splitaddr.txt \
	upscli_splitname.txt \
	upscli_ssl.txt \
	upscli_strerror.txt \
	upscli_upserror.txt \
	nutscan.txt \
	nutscan_scan_snmp.txt \
	nutscan_scan_usb.txt \
	nutscan_scan_xml_http.txt \
	nutscan_scan_nut.txt \
	nutscan_scan_avahi.txt \
	nutscan_scan_ipmi.txt \
	nutscan_display_ups_conf.txt \
	nutscan_display_parsable.txt \
	nutscan_cidr_to_ip.txt \
	nutscan_new_device.txt \
	nutscan_free_device.txt \
	nutscan_add_option_to_device.txt \
	nutscan_add_device_to_device.txt \
	nutscan_init.txt \
	libupsclient-config.txt \
	skel.txt

MAN3_DEV_PAGES = \
	upsclient.3 \
	upscli_connect.3 \
	upscli_disconnect.3 \
	upscli_fd.3 \
	upscli_get.3 \
	upscli_list_next.3 \
	upscli_list_start.3 \
	upscli_readline.3 \
	upscli_sendline.3 \
	upscli_splitaddr.3 \
	upscli_splitname.3 \
	upscli_ssl.3 \
	upscli_strerror.3 \
	upscli_upserror.3 \
	nutscan.3 \
	nutscan_scan_snmp.3 \
	nutscan_scan_usb.3 \
	nutscan_scan_xml_http.3 \
	nutscan_scan_nut.3 \
	nutscan_scan_avahi.3 \
	nutscan_scan_ipmi.3 \
	nutscan_display_ups_conf.3 \
	nutscan_display_parsable.3 \
	nutscan_cidr_to_ip.3 \
	nutscan_new_device.3 \
	nutscan_free_device.3 \
	nutscan_add_option_to_device.3 \
	nutscan_add_device_to_device.3 \
	nutscan_init.3

MAN1_DEV_PAGES = \
	libupsclient-config.1

if WITH_DEV
 man3_MANS = $(MAN3_DEV_PAGES)

if !WITH_PKG_CONFIG
 man1_MANS = $(MAN1_DEV_PAGES)
endif
# WITH_DEV
endif

HTML_DEV_MANS = \
	upsclient.html \
	upscli_connect.html \
	upscli_disconnect.html \
	upscli_fd.html \
	upscli_get.html \
	upscli_list_next.html \
	upscli_list_start.html \
	upscli_readline.html \
	upscli_sendline.html \
	upscli_splitaddr.html \
	upscli_splitname.html \
	upscli_ssl.html \
	upscli_strerror.html \
	upscli_upserror.html \
	nutscan.html \
	nutscan_scan_snmp.html \
	nutscan_scan_usb.html \
	nutscan_scan_xml_http.html \
	nutscan_scan_nut.html \
	nutscan_scan_avahi.html \
	nutscan_scan_ipmi.html \
	nutscan_display_ups_conf.html \
	nutscan_display_parsable.html \
	nutscan_cidr_to_ip.html \
	nutscan_new_device.html \
	nutscan_free_device.html \
	nutscan_add_option_to_device.html \
	nutscan_add_device_to_device.html \
	nutscan_init.html \
	libupsclient-config.html \
	skel.html


# Drivers related manpages

# (--with-drivers=...)
if SOME_DRIVERS
 man8_MANS += $(DRIVER_MAN_LIST)

else

# (--with-serial)
SRC_SERIAL_PAGES = \
	apcsmart.txt	\
	apcsmart-old.txt	\
	bcmxcp.txt 	\
	belkin.txt 	\
	belkinunv.txt	\
	bestfortress.txt	\
	bestuferrups.txt	\
	bestups.txt 	\
	bestfcom.txt	\
	blazer.txt	\
	clone.txt \
	dummy-ups.txt	\
	etapro.txt	\
	everups.txt	\
	gamatronic.txt	\
	genericups.txt	\
	isbmex.txt	\
	ivtscd.txt	\
	liebert.txt	\
	liebert-esp2.txt	\
	masterguard.txt	\
	metasys.txt	\
	mge-shut.txt	\
	mge-utalk.txt	\
	oneac.txt		\
	microdowell.txt	\
	optiups.txt	\
	powercom.txt 	\
	powerpanel.txt	\
	rhino.txt		\
	safenet.txt	\
	solis.txt		\
	tripplite.txt	\
	tripplitesu.txt	\
	upscode2.txt	\
	victronups.txt

MAN_SERIAL_PAGES = \
	apcsmart.8	\
	apcsmart-old.8	\
	bcmxcp.8 	\
	belkin.8 	\
	belkinunv.8	\
	bestfortress.8	\
	bestuferrups.8	\
	bestups.8 	\
	bestfcom.8	\
	blazer.8	\
	clone.8 \
	dummy-ups.8	\
	etapro.8	\
	everups.8	\
	gamatronic.8	\
	genericups.8	\
	isbmex.8	\
	ivtscd.8	\
	liebert.8	\
	liebert-esp2.8	\
	masterguard.8	\
	metasys.8	\
	mge-shut.8	\
	mge-utalk.8	\
	oneac.8		\
	microdowell.8	\
	optiups.8	\
	powercom.8 	\
	powerpanel.8	\
	rhino.8		\
	safenet.8	\
	solis.8		\
	tripplite.8	\
	tripplitesu.8	\
	upscode2.8	\
	victronups.8

if WITH_SERIAL
  man8_MANS +=  $(MAN_SERIAL_PAGES)
endif

HTML_SERIAL_MANS = \
	apcsmart.html	\
	apcsmart-old.html	\
	bcmxcp.html 	\
	belkin.html 	\
	belkinunv.html	\
	bestfortress.html	\
	bestuferrups.html	\
	bestups.html 	\
	bestfcom.html	\
	blazer.html	\
	clone.html \
	dummy-ups.html	\
	etapro.html	\
	everups.html	\
	gamatronic.html	\
	genericups.html	\
	isbmex.html	\
	ivtscd.html	\
	liebert.html	\
	liebert-esp2.html	\
	masterguard.html	\
	metasys.html	\
	mge-shut.html	\
	mge-utalk.html	\
	oneac.html		\
	microdowell.html	\
	optiups.html	\
	powercom.html 	\
	powerpanel.html	\
	rhino.html		\
	safenet.html	\
	solis.html		\
	tripplite.html	\
	tripplitesu.html	\
	upscode2.html	\
	victronups.html

# (--with-snmp)
SRC_SNMP_PAGES = snmp-ups.txt
MAN_SNMP_PAGES = snmp-ups.8

if WITH_SNMP
  man8_MANS += $(MAN_SNMP_PAGES)
endif

HTML_SNMP_MANS = snmp-ups.html

# (--with-usb)
SRC_USB_LIBUSB_PAGES = \
	bcmxcp_usb.txt \
	richcomm_usb.txt \
	tripplite_usb.txt \
	usbhid-ups.txt

MAN_USB_LIBUSB_PAGES = \
	bcmxcp_usb.8 \
	richcomm_usb.8 \
	tripplite_usb.8 \
	usbhid-ups.8

if WITH_USB
 man8_MANS += $(MAN_USB_LIBUSB_PAGES)
endif

HTML_USB_LIBUSB_MANS = \
	bcmxcp_usb.html \
	richcomm_usb.html \
	tripplite_usb.html \
	usbhid-ups.html

# (--with-neon)
SRC_NETXML_PAGES = netxml-ups.txt
MAN_NETXML_PAGES = netxml-ups.8

if WITH_NEON
   man8_MANS += $(MAN_NETXML_PAGES)
endif

HTML_NETXML_MANS = netxml-ups.html

# (--with-powerman)
SRC_POWERMAN_PAGES = powerman-pdu.txt
MAN_POWERMAN_PAGES = powerman-pdu.8

if WITH_LIBPOWERMAN
   man8_MANS += $(MAN_POWERMAN_PAGES)
endif

HTML_POWERMAN_MANS = powerman-pdu.html

# (--with-ipmi)
SRC_IPMIPSU_PAGES = nut-ipmipsu.txt
MAN_IPMIPSU_PAGES = nut-ipmipsu.8

if WITH_IPMI
   man8_MANS += $(MAN_IPMIPSU_PAGES)
endif

HTML_IPMIPSU_MANS = nut-ipmipsu.html

SRC_MACOSX_PAGES = macosx-ups.txt
MAN_MACOSX_PAGES = macosx-ups.8

if WITH_MACOSX
   man8_MANS += $(MAN_MACOSX_PAGES)
endif

HTML_MACOSX_MANS = macosx-ups.html

# SOME_DRIVERS
endif

MAN_MANS = \
	$(MAN_CONF_PAGES) \
	$(MAN_CLIENT_PAGES) \
	$(MAN_TOOL_PAGES) \
	$(MAN5_CGI_PAGES) \
	$(MAN8_CGI_PAGES) \
	$(MAN1_DEV_PAGES) \
	$(MAN3_DEV_PAGES) \
	$(MAN_SERIAL_PAGES) \
	$(MAN_SNMP_PAGES) \
	$(MAN_USB_LIBUSB_PAGES) \
	$(MAN_NETXML_PAGES) \
	$(MAN_POWERMAN_PAGES) \
	$(MAN_IPMIPSU_PAGES) \
	$(MAN_MACOSX_PAGES)

# distribute everything, even those not installed by default
# Note that 'dist' target requires AsciiDoc!
EXTRA_DIST = \
	$(SRC_CONF_PAGES) \
	$(SRC_CLIENT_PAGES) \
	$(SRC_TOOL_PAGES) \
	$(SRC_CGI_PAGES) \
	$(SRC_DEV_PAGES) \
	$(SRC_SERIAL_PAGES) \
	$(SRC_SNMP_PAGES) \
	$(SRC_USB_LIBUSB_PAGES) \
	$(SRC_NETXML_PAGES) \
	$(SRC_POWERMAN_PAGES) \
	$(SRC_IPMIPSU_PAGES) \
	$(SRC_MACOSX_PAGES) \
	$(MAN_MANS) \
	asciidoc.conf

HTML_MANS = \
	$(HTML_CONF_MANS) \
	$(HTML_CLIENT_MANS) \
	$(HTML_TOOL_MANS) \
	$(HTML_CGI_MANS) \
	$(HTML_DEV_MANS) \
	$(HTML_SERIAL_MANS) \
	$(HTML_SNMP_MANS) \
	$(HTML_USB_LIBUSB_MANS) \
	$(HTML_NETXML_MANS) \
	$(HTML_POWERMAN_MANS) \
	$(HTML_IPMIPSU_MANS) \
	$(HTML_MACOSX_MANS)

all:

man-index.html: index.html
	cp -f $< $@

html-man: $(HTML_MANS) man-index.html

CLEANFILES = *.xml *.html

SUFFIXES = .txt .html .1 .3 .5 .8

if HAVE_ASCIIDOC

.txt.html:
	$(ASCIIDOC) --backend=xhtml11 \
		--attribute localdate=`TZ=UTC date +%Y-%m-%d` \
		--attribute localtime=`TZ=UTC date +%H:%M:%S` \
		-o $@ $<

### The --destination-dir flag doesn't seem to affect the intermediate .xml file.
### Hence, the copying dance below.
A2X_MANPAGE_OPTS = -f manpage --attribute nutversion="@PACKAGE_VERSION@"

.txt.1:
	test -f `basename $<` || cp -p $< .
	$(A2X) $(A2X_MANPAGE_OPTS) `basename $<`

.txt.3:
	test -f `basename $<` || cp -p $< .
	$(A2X) $(A2X_MANPAGE_OPTS) `basename $<`

.txt.5:
	test -f `basename $<` || cp -p $< .
	$(A2X) $(A2X_MANPAGE_OPTS) `basename $<`

.txt.8:
	test -f `basename $<` || cp -p $< .
	$(A2X) $(A2X_MANPAGE_OPTS) `basename $<`

else !HAVE_ASCIIDOC

.txt.html:
	@echo "Not (re)building $@ manual page, since 'asciidoc' was not found."

.txt.1:
	@echo "Using existing $@ manual page, since 'asciidoc' was not found."

.txt.3:
	@echo "Using existing $@ manual page, since 'asciidoc' was not found."

.txt.5:
	@echo "Using existing $@ manual page, since 'asciidoc' was not found."

.txt.8:
	@echo "Using existing $@ manual page, since 'asciidoc' was not found."

endif !HAVE_ASCIIDOC
