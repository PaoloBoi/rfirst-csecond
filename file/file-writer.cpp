#include "file-writer.h"

/**
 * @param file_path Path del file sul quale scrivere.
 *
 * Inizializza il path del file di output, sul quale verranno scritte le informazioni.
 */
File_Writer::File_Writer(string filePath) {

    this->file_path = filePath;
    this->write_state = false;
}

/**
 * Scrive i dati sul file di output.
 */
void File_Writer::write_file(QString header, QString body) {

    if(this->open_file()) {

        qDebug("File aperto in scrittura...");

        this->out_file << header.toStdString()/* << endl*/;
        this->out_file << body.toStdString()/* << endl*/;

        this->close_file();

        this->write_state = true;
    }

    this->write_state = false;
}

/**
 * Apre il file in scrittura.
 *
 * @return TRUE se il file è stato aperto, FALSE altrimenti.
 */
bool File_Writer::open_file() {

    if(this->out_file.is_open()) { return true; }
    else {
        this->out_file.open(this->file_path.c_str(), std::iostream::out);
        return !out_file.fail();
    }
}

/**
 * Chiude il file.
 *
 * @return TRUE se il file è stato chiuso, FALSE altrimenti.
 */
bool File_Writer::close_file() {

    if(this->open_file()) {
        this->out_file.close();
        qDebug("File chiuso...");
        return true;
    }
    return false;
}
