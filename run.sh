 #!/bin/sh

#
#  Edwino Stien - 1201324411
#

# ************** Variaveis globais **************

dirBuild="./build/";
compileTool="./tools/compileOSX.sh";
compileLibTool="./tools/compileTreeLib.sh";
libName="Tree.a";
mainProgramName="main";
compileInvokation="main.cpp Util/Parser.cpp";
params="";

# ************** Programa principal **************

#Cria o diretorio onde ficaram os binarios, caso nao exista
if [ ! -d "$dirBuild" ]; then
  echo -n "Criando diretorio \"$dirBuild\"...";
  mkdir "$dirBuild";
  echo " OK"
fi

# Verifica se a biblioteca já foi compilada
if [ ! -f "$dirBuild$libName" ] ; then
	echo
	echo -e "\t   ######################################################"
	echo -e "\t   ########## Compilando biblioteca de Árvores ##########"
	echo -e "\t   ######################################################"
	echo
	chmod +x "$compileLibTool";
	bash -c "$compileLibTool";

	if [ $? -ne 0 ];  then
		echo
		echo " ***** Algo errado ocorreu durante a compilação da biblioteca *****"
		exit 1;
	fi

	echo
fi

#Verifica se o aplicativo já foi compilado
if [ ! -f "$dirBuild$mainProgramName" ] ; then
	echo
	echo -e "\t   ######################################################"
	echo -e "\t   ################ Compilando Aplicativo ###############"
	echo -e "\t   ######################################################"
	echo
	chmod +x "$compileTool";
	bash -c "$compileTool $compileInvokation";

	if [ $? -ne 0 ];  then
		echo
		echo " ***** Algo errado ocorreu durante a compilação do aplicativo *****"
		exit 1;
	fi
	echo
fi

echo
echo -e "\t   ######################################################"
echo -e "\t   ################ Executando Aplicativo ###############"
echo -e "\t   ######################################################"
echo

#Pega os parâmetros
for i in `seq 1 $#`
do
	eval "params=\"$params \$$i\"";
done;

#Executa o aplicativo
chmod +x "$dirBuild$mainProgramName";
bash -c "$dirBuild$mainProgramName $params";

exit 0;