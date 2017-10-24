# padthv1_lv2ui.pro
#
NAME = padthv1

TARGET = $${NAME}_lv2ui
TEMPLATE = lib
CONFIG += shared plugin
LIBS += -L.

include(src_lv2.pri)

HEADERS = \
	config.h \
	padthv1_ui.h \
	padthv1_lv2ui.h \
	padthv1widget.h \
	padthv1widget_env.h \
	padthv1widget_filt.h \
	padthv1widget_sample.h \
	padthv1widget_wave.h \
	padthv1widget_param.h \
	padthv1widget_preset.h \
	padthv1widget_status.h \
	padthv1widget_programs.h \
	padthv1widget_controls.h \
	padthv1widget_control.h \
	padthv1widget_config.h \
	padthv1widget_lv2.h

SOURCES = \
	padthv1_lv2ui.cpp \
	padthv1widget_lv2.cpp


unix {

	OBJECTS_DIR = .obj_lv2ui
	MOC_DIR     = .moc_lv2ui
	UI_DIR      = .ui_lv2ui

	isEmpty(PREFIX) {
		PREFIX = /usr/local
	}

	isEmpty(LIBDIR) {
		TARGET_ARCH = $$system(uname -m)
		contains(TARGET_ARCH, x86_64) {
			LIBDIR = $${PREFIX}/lib64
		} else {
			LIBDIR = $${PREFIX}/lib
		}
	}

	contains(PREFIX, $$system(echo $HOME)) {
		LV2DIR = $${PREFIX}/.lv2
	} else {
		LV2DIR = $${LIBDIR}/lv2
	}

	TARGET_LV2UI = $${NAME}.lv2/$${NAME}_ui

	!exists($${TARGET_LV2UI}.so) {
		system(touch $${TARGET_LV2UI}.so)
	}

	!exists($${TARGET_LV2UI}.ttl) {
		system(touch $${TARGET_LV2UI}.ttl)
	}

	INSTALLS += target

	target.path  = $${LV2DIR}/$${NAME}.lv2
	target.files = $${TARGET_LV2UI}.so $${TARGET_LV2UI}.ttl

	QMAKE_POST_LINK += $${QMAKE_COPY} -vp $(TARGET) $${TARGET_LV2UI}.so

	greaterThan(QT_MAJOR_VERSION, 4) {
		QMAKE_POST_LINK += ;\
			$${QMAKE_COPY} -vp $${TARGET_LV2UI}-qt5.ttl $${TARGET_LV2UI}.ttl
	} else {
		QMAKE_POST_LINK += ;\
			$${QMAKE_COPY} -vp $${TARGET_LV2UI}-qt4.ttl $${TARGET_LV2UI}.ttl
	}

	QMAKE_CLEAN += $${TARGET_LV2UI}.so $${TARGET_LV2UI}.ttl

	LIBS += -l$${NAME} -l$${NAME}_ui -L$${NAME}.lv2 -Wl,-rpath,$${LIBDIR}:$${LV2DIR}/$${NAME}.lv2
}

QT += xml

# QT5 support
greaterThan(QT_MAJOR_VERSION, 4) {
	QT += widgets
}
