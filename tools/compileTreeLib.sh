#!/bin/sh

#
#  Edwino Stien - 1201324411
#

# ************** Variaveis globais **************
fileLog="compile.log";
dirBuild="build/";
outputLibName="Tree.a";
srcFiles=("BinaryTree.cpp" "AvlTree.cpp" "BTree");
srcFolder="Tree/src/";
compilerFlags='-std=c++11 -Wall -Werror';
generateLib="ar rvs"
dependencies='';
success=1;
error='';
errorDesc='';
gccCode=0;
warnings=0;
BASE_DIR="";

# ************** Sub-rotinas **************

setBaseDir(){
    SOURCE="${BASH_SOURCE[0]}"
    BASE_DIR="$( cd -P "$( dirname "$SOURCE" )/../" && pwd )/"
}

# Função que remove apenas a extensão de um arquivo
function removeExtension(){
	fileName=`echo ${1} | cut -f1 -d'.'`
}

# Função que retorna apenas o nome do arquivo sem extensão
function getFileName(){
	fileName=`basename $1`;
	removeExtension $fileName;
}

# Função que realiza a compilação do codigo fonte em um codigo objeto
function compile(){

	success=1;
	errorDesc='';

	removeExtension $1;
	src="${fileName}.cpp";

	# Verifica se o arquivo fonte existe
	if [ ! -f "$src" ] ; then
	    success=0;
	    gccCode=1;
	    error="O arquivo \"${fileName}.cpp\" não é invalido ou não existe!"
	    return;
	fi

	getFileName $1;
	target=$fileName;

	# Remove arquivo objeto antigo, se existir
	if [ -e '${dirBuild}${target}.o' ] ; then
	    rm '${dirBuild}${target}.o'
	fi

	# Compila o arquivo fonte e pega a saida e o codigo do G++
	compilerInvocation="g++ ${compilerFlags} -o ${dirBuild}${target}.o -c ${src}";
	bash -c "$compilerInvocation > compile.log 2>&1";
	gccCode=$?;
	
	# Salva o arquivo de log gerado em uma varaivel e o remove
	errorDesc=$(<compile.log);
	rm "compile.log";

	#Verifica se ocorreu algum erro

	if [ $gccCode -ne 0 ];  then
		success=0;
		error="Ocorreu algum erro durante a compilação de \"${fileName}\"";
		return;
	fi

	# Verifica se ocorreu algum alerta
	if [ -n "$errorDesc" ]; then
		success=0;
		error="Ocorreu algum alerta durante a compilação de \"${fileName}\"";
		gccCode=2;
		return;
	fi
}

#Função verifica o nivel do erro e o exibe na tela
function checkError(){

	if [ $success -ne 1 ];  then
		if [ $gccCode -ne 1 ];  then
			echo " Alerta!";
			echo "$error";
			echo;
			echo "********************** DESCRIÇÃO DO ALERTA **********************";
			echo "$errorDesc";
			echo "*****************************************************************";
			echo;
			warnings=$(($warnings + 1));
		else
			echo " Falhou!";
			echo "$error";
			echo;
			echo "********************** DESCRIÇÃO DO ERRO **********************";
			echo "$errorDesc";
			echo "***************************************************************";
			echo;
			echo "O processo foi abortado!";
			exit 1;
		fi
	else
		echo " OK!";
	fi

}

# ************** Programa principal **************

#Cria o diretorio onde ficaram os binarios, caso nao exista
if [ ! -d "$BASE_DIR$dirBuild" ]; then
  echo -n "Criando diretorio \"$dirBuild\"...";
  mkdir "$BASE_DIR$dirBuild";
  echo " OK"
fi

# Percorre a lista com os arquivos que deve compilar
for i in "${srcFiles[@]}"
do
	echo -n "Compilando \"$srcFolder$i\"...";
	compile $srcFolder$i;
	checkError;

	getFileName $i
	dependencies="$dependencies ${dirBuild}${fileName}.o";
done;

echo -n "Gerando biblioteca estática \"$dirBuild$outputLibName\"...";

#Se a biblioteca já existe, remove
if [ -e '$dirBuild$outputLibName' ] ; then
    rm '$dirBuild$outputLibName'
fi

invocation="$generateLib $dirBuild$outputLibName $dependencies"
bash -c "$invocation > compile.log 2>&1";
gccCode=$?;

# Salva o arquivo de log gerado em uma varaivel e o remove
errorDesc=$(<compile.log);
rm "compile.log";

if [ $gccCode -ne 0 ];  then
	echo " Falhou!";
	echo;
	echo "******* Houve erros durante a compilação da biblioteca! *******";
	echo "$errorDesc";
	echo "***************************************************************";
	echo;
	exit 1;
fi
echo " OK!";

#remove os arquivos objetos que forma utilizados
echo -n "Limpando bagunça...";
bash -c "rm $dependencies > /dev/null";
echo " OK!";
exit 0;
