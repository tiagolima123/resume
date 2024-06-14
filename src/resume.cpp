#include "resume.h"
#include <QFile>
#include <QDebug>
#include <QPageSize>
#include <QStaticText>

Resume::Resume(QObject *parent)
	: QObject(parent) {
	
	sw = 9500./720.;
	sh = 13500./1024.;
}


void Resume::craft(const QString &filePath) {
	output = filePath;


	QPrinter printer(QPrinter::HighResolution);
	printer.setOutputFormat(QPrinter::PdfFormat);
	printer.setOutputFileName(output);

	QPainter painter(&printer);
	
	
	if (!printer.isValid() || !painter.isActive()) {
	    qDebug() << "Export Error" << "Failed to initialize printer for PDF output";
	    return;
	}


	/*PRESENTATION*/
	drawUsername(painter);
	drawTitle(painter);
	drawAddress(painter);
	drawContact(painter);
	drawAvatar(painter);

	/*ABOUT ME*/
	drawProfile(painter);
	drawSkills(painter);;
	drawLanguages(painter);
	drawDetails(painter);
	drawGithub(painter);
	painter.end();
}


void Resume::drawText(QPainter &painter, 
	/* text*/ QPoint pos, QString text, 
	/*brush*/ QColor brush_color, Qt::BrushStyle brush_style,
	/*  pen*/ int pen_size, Qt::PenStyle pen_style,
	/* font*/ QFont font) { 
	
	QBrush brush(brush_color);
	brush.setStyle(brush_style);
	
	QPen pen(brush, pen_size);
	pen.setStyle(pen_style);

	painter.setPen(pen);
	painter.setFont(font);

	QRect text_rect(pos, QSize(pen_size, 1000*sh));
	int text_flags = Qt::AlignLeft | Qt::AlignTop;
	painter.drawText(text_rect, text_flags, text);


}
	
QString Resume::catFile(QString filename) {
	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	if (not file.isOpen()) {
		qDebug() << "Warning" << "Could not open" << filename;
		return "";
	}
	
	QString data = file.readAll().toStdString().c_str();
	file.close();
	return data;
}

void Resume::drawMultiArcs(QPainter &painter, int total, int start_x, int y, int r) {
	
	QImage arc("images/arc.png");
	arc = arc.scaled(QSize(r, r));
		

	for (int i=0; i<total; i++) {
		painter.drawImage(QPoint(start_x-i*(r+2), y), 
				  arc, arc.rect());
	}
	
}


void Resume::drawUsername(QPainter &painter) {
	drawText(painter, 
		QPoint(30*sw, 40*sh), "TIAGO TEIXEIRA DE LIMA",
		Qt::black, Qt::SolidPattern,
		500*sw, Qt::SolidLine,
		QFont("Lora", 28));
}


void Resume::drawTitle(QPainter &painter) {
	QColor brush_color(100, 100, 100, 255);
	drawText(painter, 
		QPoint(30*sw, 110*sh), "programmer",
		brush_color, Qt::SolidPattern,
		200*sh, Qt::SolidLine,
		QFont("Helvetica", 10));
}

void Resume::drawAddress(QPainter &painter) {
	QColor brush_color(100, 100, 100, 255);

	drawText(painter, 
		QPoint(30*sw, 130*sh), "rúa do campo, Apíai/SP, 18324-000",
		brush_color, Qt::SolidPattern,
		200*sh, Qt::SolidLine,
		QFont("Helvetica", 10));

	drawText(painter, 
		QPoint(30*sw, 150*sh), "Brasil",
		brush_color, Qt::SolidPattern,
		200*sh, Qt::SolidLine,
		QFont("Helvetica", 10));
}

void Resume::drawContact(QPainter& painter) {
	QColor brush_color(100, 100, 100, 255);


	drawText(painter, 
		QPoint(300*sw, 130*sh), "+55 (15) 99717-5374",
		brush_color, Qt::SolidPattern,
		200*sh, Qt::SolidLine,
		QFont("Helvetica", 10));


	drawText(painter, 
		QPoint(300*sw, 150*sh), "tiagotlimadev5@gmail.com",
		brush_color, Qt::SolidPattern,
		200*sh, Qt::SolidLine,
		QFont("Helvetica", 10));
}

void Resume::drawAvatar(QPainter &painter) {

	QImage avatar("images/avatar.png");
	avatar = avatar.scaled(QSize(150*sw, 159*sh));

	painter.drawImage(QPoint(550*sw, 20*sh), avatar, avatar.rect());

}

	
void Resume::drawProfile(QPainter &painter) {
	
	drawText(painter, 
		QPoint(30*sw, 210*sh), "PROFILE",
		Qt::black, Qt::SolidPattern,
		200*sh, Qt::SolidLine,
		QFont("Lora", 25));

	QString profile = catFile("texts/profile.txt"); 
	QColor brush_color(100, 100, 100, 255);

	drawText(painter,
		QPoint(30*sw, 260*sh), profile,
		brush_color, Qt::SolidPattern,
		600*sh, Qt::SolidLine,
		QFont("Helvetica", 10));

}


void Resume::drawSkills(QPainter &painter) {
	
	drawText(painter, 
		QPoint(30*sw, 430*sh), "SKILLS",
		Qt::black, Qt::SolidPattern,
		200*sh, Qt::SolidLine,
		QFont("Lora", 25));
	
	QStringList skills = catFile("texts/skills.txt").split("\n");
	QColor brush_color(100, 100, 100, 255);

	int y = 480;
	for (QString skill : skills) {
		QStringList skill_level = skill.split(":");
		if (skill_level.count() != 2)
			continue;

		drawText(painter,
			QPoint(30*sw, y*sh), skill_level[0],
			brush_color, Qt::SolidPattern,
			200*sh, Qt::SolidLine,
			QFont("Helvetica", 10));

		drawMultiArcs(painter, skill_level[1].toInt(), 300*sw, y*sh, 20*sw);
		y+=20;
	}
}


void Resume::drawLanguages(QPainter &painter) {	
	drawText(painter, 
		QPoint(350*sw, 430*sh), "LANGUAGES",
		Qt::black, Qt::SolidPattern,
		200*sh, Qt::SolidLine,
		QFont("Lora", 25));
	
	QStringList languages = catFile("texts/languages.txt").split("\n");
	QColor brush_color(100, 100, 100, 255);

	int y = 480;
	for (QString language : languages) {
		QStringList language_level = language.split(":");
		if (language_level.count() != 2)
			continue;

		drawText(painter,
			QPoint(350*sw, y*sh), language_level[0],
			brush_color, Qt::SolidPattern,
			200*sh, Qt::SolidLine,
			QFont("Helvetica", 10));

		drawMultiArcs(painter, language_level[1].toInt(), 600*sw, y*sh, 20*sw);
		y+=20;
	}
}


void Resume::drawDetails(QPainter &painter) {	
	drawText(painter, 
		QPoint(30*sw, 750*sh), "DETAILS",
		Qt::black, Qt::SolidPattern,
		200*sh, Qt::SolidLine,
		QFont("Lora", 25));
	
	QStringList details = catFile("texts/details.txt").split("\n");
	QColor brush_color(100, 100, 100, 255);

	int y = 800;
	for (QString detail : details) {
		QStringList about = detail.split(":");
		if (about.count() != 2)
			continue;

		drawText(painter,
			QPoint(30*sw, y*sh), about[0],
			brush_color, Qt::SolidPattern,
			200*sh, Qt::SolidLine,
			QFont("Helvetica", 10));

		drawText(painter,
			QPoint(350*sw, y*sh), about[1],
			brush_color, Qt::SolidPattern,
			400*sh, Qt::SolidLine,
			QFont("Helvetica", 10));

		y+=20;
	}
}


void Resume::drawGithub(QPainter &painter) {

	QString text = "This résumé was written using C++ and Qt -> ";

	QColor brush_color_gray(100, 100, 100, 255);

	drawText(painter, 
		QPoint(30*sw, 1000*sh), text,
		brush_color_gray, Qt::SolidPattern,
		720*sh, Qt::SolidLine,
		QFont("Lora", 10));

	QColor brush_color_baby_blue(137, 207, 240, 255);
	QString linkUrl = "https://github.com/tiagolima123/resume";

	drawText(painter, 
		QPoint(300*sw, 1000*sh), linkUrl,
		brush_color_baby_blue, Qt::SolidPattern,
		720*sh, Qt::SolidLine,
		QFont("Lora", 10));

}


