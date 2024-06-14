#ifndef __RESUME_H__
#define __RESUME_H__

#include <QObject>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPrinter>

class Resume : public QObject {
public:	
	Resume(QObject *parent=nullptr);

	void craft(const QString &filePath);

private:

	void drawText(QPainter &painter, 
		/* text*/ QPoint pos, QString text,
		/*brush*/ QColor brush_color=Qt::black,
			  Qt::BrushStyle brush_style=Qt::SolidPattern,
		/*  pen*/ int pen_size=15, 
			  Qt::PenStyle penStyle=Qt::SolidLine,
		/* font*/ QFont font=QFont());

	QString catFile(QString);

	void drawMultiArcs(QPainter&, int total, int start_x, int y, int r=50);

	/*PRESENTATION*/
	void drawUsername(QPainter&);
	void drawTitle(QPainter&);
	void drawAddress(QPainter&);
	void drawContact(QPainter&);
	void drawAvatar(QPainter&);

	/*ABOUT ME*/
	void drawProfile(QPainter&);
	void drawSkills(QPainter&);
	void drawLanguages(QPainter&);
	void drawDetails(QPainter&);

	/*END*/
	void drawGithub(QPainter&);


	QString output;
	float sw, sh;


};

#endif
