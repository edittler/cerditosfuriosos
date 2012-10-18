MSJ_DISENADOR = @echo "::::::Instalando Diseñador::::::"
MSJ_CLIENTE = @echo "::::::Instalando Cliente::::::"
MSJ_SERV = @echo "::::::Instalando Servidor::::::"

MSJ_ESP = @echo "..."

MSJ_DESINS = @echo "Desinstalando "

MSJ_DOCS = @echo "Generando documentación..."


all: install

install: uninstall install_designer install_client install_server

install_designer:
	$(MSJ_DISENADOR);mkdir Diseñador 
	$(MSJ_ESP);cd designer; make --no-print-directory -s 
	$(MSJ_ESP);cp designer/main Diseñador 

	
install_client:
	$(MSJ_CLIENTE);mkdir Cliente 
	$(MSJ_ESP);cd client; make --no-print-directory -s 
	$(MSJ_ESP);cp -f client/main Cliente 
	

install_server:
	$(MSJ_SERV); mkdir Servidor
	$(MSJ_ESP);cd server; make --no-print-directory -s
	$(MSJ_ESP);cp -f server/main Servidor


doc:
	$(MSJ_DOCS); doxygen doxyConfig

debug:
	rm -r -f DEBUG_RELEASE
	mkdir DEBUG_RELEASE
	cd designer; make DEBUG=yes
	mkdir DEBUG_RELEASE/designer
	cp designer/main DEBUG_RELEASE/designer
	cp designer/*.conf DEBUG_RELEASE/designer
	cp designer/*.config DEBUG_RELEASE/designer
	cd server; make DEBUG=yes
	mkdir DEBUG_RELEASE/server
	cp -f server/main DEBUG_RELEASE/server
	cp -f server/*.conf DEBUG_RELEASE/server
	cp -f server/*.config DEBUG_RELEASE/server
	cp -f server/*.dat DEBUG_RELEASE/server
	mkdir DEBUG_RELEASE/client 
	cd cliente; make DEBUG=yes 
	cp -f client/main DEBUG_RELEASE/client 
	cp -f client/*.conf DEBUG_RELEASE/client 
	cp -f client/*.config DEBUG_RELEASE/client
	cp -f client/*.glade DEBUG_RELEASE/client
	cp -f client/*.png DEBUG_RELEASE/client
	cp -f client/*.xml DEBUG_RELEASE/client 
	
	 	
uninstall:
	$(MSJ_DESINS)
	$(MSJ_ESP);rm -f -r Diseñador
	$(MSJ_ESP);rm -f -r Servidor
	$(MSJ_ESP);rm -f -r Cliente
	$(MSJ_ESP);rm -f -r DEBUG_RELEASE


.PHONY: all install	install_designer install_client install_server	uninstall debug doc
