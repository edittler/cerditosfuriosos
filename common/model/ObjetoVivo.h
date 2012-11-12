#ifndef OBJETOVIVO_H
#define	OBJETOVIVO_H

class ObjetoVivo {
    public:
        ObjetoVivo();
        virtual ~ObjetoVivo();

        virtual void vivir(int milisegundos) = 0;
};

#endif

