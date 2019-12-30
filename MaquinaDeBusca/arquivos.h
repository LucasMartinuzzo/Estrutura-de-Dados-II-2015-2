#ifndef ARQUIVOS_H
#define	ARQUIVOS_H

#define TAM_FILE 260
#define TAM_TERMO 10000

char *retirarAcentos(char*, char);

int carregarArquivoEnc();

int carregarListaArquivosEnc();

int carregarArquivoLin();

int carregarListaArquivosLin();

int carregarArquivoDup();

int carregarListaArquivosDup();

int carregarListaBusca();

int salvarIndexLinDup();

int salvarIndexEnc();

int carregarIndexLinDup();

int carregarIndexEnc();

#endif	/* ARQUIVOS_H */