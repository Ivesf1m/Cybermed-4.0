#!/bin/bash

#Script configs
verde=[42m
vermelho=[41m
normal=[0m
libcybpath="/usr/lib"

#modules
core=0
view=0
util=0
assess=0
collision=0
haptics=0
optical_trackers=0
magnetic_trackers=0
deformation=0
network=0
collaboration=0
gloves=0

# Only root can execute this script!

if [[ $EUID -ne 0 ]]; then
	echo ${vermelho}"Problems executing script!" ${normal} 1>&2
        echo ${vermelho}"Are you root?" ${normal} 1>&2
	exit 1
fi

function error_dependence
{
	echo ${vermelho}"Dependence problem: Module $1 not installed!."${normal}
	exit 1
}

function error_removing
{
	echo ${vermelho}"Error removing $1. Aborting..."${normal}
	exit 1
}

function error_exit
{
	echo ${vermelho}"Problems installing $1. Aborting ..."${normal}
	exit 1
}

installLibrary(){

   #Verifica se a pasta cybermed já existe no diretório include
   [ -e /usr/include/cybermed ] || mkdir /usr/include/cybermed

   #Verifica se a pasta cybermed já existe no diretório src
   [ -e /usr/src/cybermed ] || mkdir /usr/src/cybermed


   #Util ----------------------------------------
   if [ $util = 1 ]
   then
      echo "${verde}Installing Utils ...${normal}"

      make -C Utils || error_exit "Utils"
	  make install -C Utils || error_exit "Utils"
 
      echo "Utils Installed..."
   fi
	
   #Core -----------------------------------------
   if [[ $core = 1 ]]
   then
	   echo "${verde}Installing Core ...${normal}"
	   [ -e ${libcybpath}/libcybutil.so ] || error_dependence "Util"
	   optHaptic=""      
	   optCollaboration=""	
	   optOptTracker=""
	   optMagTracker=""
       optGloves=""
       
       if [ -e ${libcybpath}/libcybcore.so ]
       then
       make clean -C Core
       make uninstall -C Core
       fi
       
       if [[ $haptics = 1 || -e ${libcybpath}/libcybhaptics.so ]]
	   then
			optHaptic="HAPTIC_OPT=\"-DCYBHAPTICS_H\""			
	   fi

	   if [[ $collaboration = 1 || -e ${libcybpath}/libcybcollaboration.so ]]
	   then			
			optCollaboration="COLLAB_OPT=\"-DCYBCOLLABORATION_H\""
	   fi
#--------------------------------------------------------------------------------------------------
# There are one lib for both trackers, thus, the file .cyb is used to indicate the tracker's type. 
#--------------------------------------------------------------------------------------------------
	   if [[ $optical_trackers = 1 || -e Trackers/optical_trackers.cyb ]]
	   then 
			optOptTracker="TRACKOPT_OPT=\"-DCYBOPTICALTRACKER_H\""
			if [ ! -e Trackers/optical_trackers.cyb ]
			then
				echo 'optical_tracker' > Trackers/optical_trackers.cyb
			fi	
	   fi
		
	   if [[ $magnetic_trackers = 1 || -e Trackers/magnetic_trackers.cyb ]]
	   then
			optMagTracker="TRACKMAG_OPT=\"-DCYBMAGNETICTRACKER_H\""
			if [ ! -e Trackers/optical_trackers.cyb ]
			then
				echo 'magnetic_trackers' > Trackers/magnetic_trackers.cyb
			fi	
	   fi

	   if [[ $gloves = 1 || -e ${libcybpath}/libcybglove.so ]]
	   then 
			optGloves="GLOVE_OPT=\"-DCYBGLOVE_H\""
	   fi    	
		
		
	  make $optHaptic $optCollaboration $optOptTracker $optMagTracker $optGloves -C Core || error_exit "Core"
      make install -C Core || error_exit "Core"
      echo "Core Installed..."
   fi

   #View -----------------------------------------
   if [ $view = 1 ]
   then
      echo "${verde}Installing View ...${normal}"
      [ -e ${libcybpath}/libcybutil.so ] || error_dependence "Util"
      [ -e ${libcybpath}/libcybcore.so ] || error_dependence "Core"

      if [ $haptics = 1 ]
      	then
        	 make HAPTIC_OPT="-DCYBHAPTICS_H" -C View || error_exit "View"
      fi
      if [ $optical_trackers = 1 ]
        then
            make TRACK_OPT="-DCYBOPTICALTRACKER_H" -C  View || error_exit "View"
      fi

	  if [ $magnetic_trackers = 1 ]
        then
            make TRACK_OPT="-DCYBMAGNETICTRACKER_H" -C  View || error_exit "View"
      fi

      make -C View || error_exit "View"
      make install -C View || error_exit "View"

      echo "View Installed..."
   fi
   
   #Collision ------------------------------------
   if [ $collision = 1 ]
   then
      echo "${verde}Installing Collision ...${normal}"

      [ -e ${libcybpath}/libcybutil.so ] || error_dependence "Util"
      [ -e ${libcybpath}/libcybcore.so ] || error_dependence "Core"

      make -C Collision || error_exit "Collision"
      make install -C Collision || error_exit "Collision"
      echo "Collision Installed..."
   fi
   
   #Deformation ----------------------------------
   if [ $deformation = 1 ]
   then
      echo "${verde}Installing Deformation ...${normal}"

      [ -e ${libcybpath}/libcybutil.so ] || error_dependence "Util"
      [ -e ${libcybpath}/libcybcore.so ] || error_dependence "Core"
      [ -e ${libcybpath}/libcybcollision.so ] || error_dependence "Collision"

      make -C Deformation || error_exit "Deformation"
      make install -C Deformation || error_exit "Deformation"

      echo "Deformation Installed..."
   fi
   
   #Haptics --------------------------------------	
   if [ $haptics = 1 ]
   then
      echo "${verde}Installing Haptics ...${normal}"

      [ -e ${libcybpath}/libcybutil.so ] || error_dependence "Util"
      [ -e ${libcybpath}/libcybcore.so ] || error_dependence "Core"

      make -C Haptics || error_exit "Haptics"
      make install -C Haptics || error_exit "Haptics"

      echo "Haptics Installed..."
   fi
   
   #Gloves ----------------------------------------
   if [ $gloves = 1 ]
   then
   	echo "${verde}Intalling Gloves ...${normal}"
   	
   	[ -e ${libcybpath}/libcybutil.so ] || error_dependence "Util"
    [ -e ${libcybpath}/libcybcore.so ] || error_dependence "Core"
   	
   	make -C Gloves || error_exit "Gloves"
   	make install -C Gloves || error_exit "Gloves"
   	
   	echo "Gloves Installed..."
   fi

   #Optical Trackers -----------------------------
   if [ $optical_trackers = 1 ]
   then
      echo "${verde}Installing Optical Trackers ...${normal}"

      [ -e ${libcybpath}/libcybutil.so ] || error_dependence "Util"
      [ -e ${libcybpath}/libcybcore.so ] || error_dependence "Core"

      make TRACK_OPT="-DCYBOPTICALTRACKER_H" -C Trackers || error_exit "Trackers"
      make install -C Trackers || error_exit "Trackers"

      echo "Optical Trackers Installed..."
   fi

   #Magnetic Trackers ----------------------------
   if [ $magnetic_trackers = 1 ]
   then
      echo "${verde}Installing Magnetic Trackers ...${normal}"

      [ -e ${libcybpath}/libcybutil.so ] || error_dependence "Util"
      [ -e ${libcybpath}/libcybcore.so ] || error_dependence "Core"

      make TRACK_OPT="-DCYBMAGNETICTRACKER_H" -C Trackers || error_exit "Trackers"
      make install -C Trackers || error_exit "Trackers"

      echo "Magnetic Trackers Installed..."
   fi


   #Asses ----------------------------------------
   if [ $assess = 1 ]
   then
      echo "${verde}Installing Assess ...${normal}"

      [ -e ${libcybpath}/libcybutil.so ] || error_dependence "Util"
      [ -e ${libcybpath}/libcybcore.so ] || error_dependence "Core"

      make -C Assess || error_exit "Assess"
      make install -C Assess || error_exit "Assess"

      echo "Assess Installed..."
   fi

   #Network --------------------------------------
   if [ $network = 1 ]
   then
      echo "${verde}Installing Network...${normal}"
      
	  make -C Network || error_exit "Network"
      make install -C Network || error_exit "Network" 
      echo "Network Installed..."
   fi
   
   #Collaboration --------------------------------
   if [ $collaboration = 1 ]
   then
      echo "${verde}Installing Collaboration...${normal}"
   	  [ -e ${libcybpath}/libcybnetwork.so ] || error_dependence "Network"
   	  
   	   optHaptic=""
   	   optHapticAssisted=""      
       optGloves=""
       optCollision=""
       optDeformation=""
            
       if [ -e ${libcybpath}/libcybcollaboration.so ]
       then
       make clean -C Collaboration
       make uninstall -C Collaboration
       fi
       
      if [[ $haptics = 1 || -e ${libcybpath}/libcybhaptics.so ]]
	  then
			optHaptic='HAPTIC_FILE=cybHapticCollaboration.cpp'
			optHapticAssisted='HAPTIC_ASSISTED_FILE=cybHapticAssistedCollab.cpp'
	  fi

	  if [[ $gloves = 1 || -e ${libcybpath}/libcybglove.so ]]
	  then 
			optGloves='GLOVE_FILE=cybGloveCollaboration.cpp'
	  fi 
   	
	  if [[ $collision = 1 || -e ${libcybpath}/libcybcollision.so ]]
      then
      		optCollision="COLLISION_OPT=\"-DCYBCOLLISION_H\""	
      fi

	  if [[ $deformation = 1 || -e ${libcybpath}/libcybdeformation.so ]]
      then
      		optDeformation="DEFORMATION_OPT=\"-DCYBDEFORMATION_H\""
      fi
      
      make $optHaptic $optGloves $optCollision $optDeformation  -C Collaboration || error_exit "Collaboration"
      make install -C Collaboration || error_exit "Collaboration" 
      echo "Collaboration Installed..."
   fi
}


uninstallLibrary(){


   if [[ $util = 1 && ( -e ${libcybpath}/libcybutil.so ) ]]
   then
      echo "Removing Utils ..."
      make uninstall -C Utils || error_removing "Utils"
      echo "Utils Removed..."
   fi

   if [[ $core = 1 && ( -e ${libcybpath}/libcybcore.so )  ]]
   then
      echo "Removing Core ..."
      make uninstall -C Core || error_removing "Core"
      echo "Core Removed"
   fi

   if [[ $view = 1 && ( -e ${libcybpath}/libcybview.so ) ]]
   then
      echo "Removing View ..."
      make uninstall -C View || error_removing "View"
      echo "View Removed"
   fi

   if [[ $collision = 1 && ( -e ${libcybpath}/libcybcollision.so ) ]]
   then
      echo "Removing Collision ..."
      make uninstall -C Collision || error_removing "Collision"
      echo "Collision Removed"
   fi

   if [[ $deformation = 1 && ( -e ${libcybpath}/libcybdeformation.so ) ]]
   then
      echo "Removing Deformation ..."
      make uninstall -C Deformation || error_removing "Deformation"
      echo "Deformation Removed"
   fi

   if [[ $haptics = 1 && ( -e ${libcybpath}/libcybhaptics.so ) ]]
   then
      echo "Removing Haptics ..."
      make uninstall -C Haptics || error_removing "Haptics"
      echo "Haptics Removed"
   fi
   
   if [[ $optical_trackers = 1 && ( -e ${libcybpath}/libcybtrackers.so ) ]]
   then
      echo "Removing Trackers ..."
      make uninstall -C Trackers || error_removing "Trackers"
      echo "Trackers Removed"
      #------
      rm Trackers/optical_trackers.cyb
   fi
   
   if [[ $gloves = 1 && ( -e ${libcybpath}/libcybglove.so ) ]]
   then 
   	echo "Removing Gloves..."
   	make uninstall -C Gloves || error_removing "Gloves"
   	echo "Gloves Removed"
   fi

   if [[ $magnetic_trackers = 1 && ( -e ${libcybpath}/libcybtrackers.so ) ]]
   then
      echo "Removing Trackers ..."
      make uninstall -C Trackers || error_removing "Trackers"
      echo "Trackers Removed"
      #------
      rm Trackers/magnetic_trackers.cyb
   fi

   if [[ $assess = 1 && ( -e ${libcybpath}/libcybasses.so ) ]]
   then
      echo "Removing Assess ..."
      make uninstall -C Assess || error_removing "Assess"
      echo "Assess Removed"
   fi

   if [[ $network = 1 && ( -e ${libcybpath}/libcybnetwork.so ) ]]
   then
      echo "Removing Network..."
      make uninstall -C Network || error_removing "Network"
      echo "Network Removed..."
   fi
   
   if [[ $collaboration = 1 && ( -e ${libcybpath}/libcybcollaboration.so ) ]]
   then
      echo "Removing Collaboration..."
      make uninstall -C Collaboration || error_removing "Collaboration"
      echo "Collaboration Removed..."
   fi

   removedAll=1
   [ ! -e /usr/lib64/libcybutil.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybcore.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybview.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybcollision.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybdeformation.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybhaptics.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybglove.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybtrackers.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybassess.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybnetwork.so ] || removedAll=0
   [ ! -e /usr/lib64/libcybcollaboration.so ] || removedAll=0	
   if [ $removedAll = 1 ]
   then
      echo "Cybermed was completely removed. Removing all data..."
      rm -rf /usr/include/cybermed
      rm -rf /usr/src/cybermed
   fi

}

cleandata(){

        
   if [ $util = 1 ]
   then
      echo "Cleaning Utils ..."
      make clean -C Utils
      echo "Utils cleaned"
   fi

   if [ $core = 1 ]
   then
      echo "Cleaning Core ..."
      make clean -C Core
      echo "Core cleaned"
   fi

   if [ $view = 1 ]
   then
      echo "Cleaning View ..."
      make clean -C View
      echo "View cleaned"
   fi

   if [ $collision = 1 ]
   then
      echo "Cleaning Collision ..."
      make clean -C Collision
      echo "Collision cleaned"
   fi

   if [ $deformation = 1 ]
   then
      echo "Cleaning Deformation ..."
      make clean -C Deformation
      echo "Deformation cleaned"
   fi

   if [ $haptics = 1 ]
   then
      echo "Cleaning Haptics ..."
      make clean -C Haptics
      echo "Haptics cleaned"
   fi
   
   if [ $optical_trackers = 1 ]
   then
      echo "Cleaning Trackers ..."
      make clean -C Trackers
      echo "Trackers cleaned"
   fi
   if [ $gloves = 1 ]
   then
   	echo 
   	make clean -C Gloves
  		echo "Gloves cleaned"
  	fi 

   if [ $magnetic_trackers = 1 ]
   then
      echo "Cleaning Trackers ..."
      make clean -C Trackers
      echo "Trackers cleaned"
   fi

   if [ $assess = 1 ]
   then
      echo "Cleaning Assess ..."
      make clean -C Assess
      echo "Assess cleaned"
   fi

   if [ $network = 1 ]
   then
      echo "Cleaning Network..."
      make clean -C Network
      echo "Network cleaned"
   fi
	
   if [ $collaboration = 1 ]
   then
      echo "Cleaning Collaboration..."
      make clean -C Collaboration
      echo "Collaboration cleaned"
   fi		
	
}

menu(){
   echo "Use - ./packmanager <valid action>"
   echo "                                        Valid Action"
   echo "##########################################################################################################"
   echo
   echo "${verde}install [parameters]${normal} - Install the indicated modules. If no module was indicated a default installation will be executed"
   echo "${verde}uninstall [parameters]${normal} - Remove the indicated module. If no module was indicated, defaults modules will be removed"
   echo "${verde}clean${normal} - Clean all source dirs"
   echo "${verde}help${normal} - Show this menu"
   echo
   echo "##########################################################################################################"
}


if [ $# != 0 ]
then
   action=$1

      shift

      if [ $# = 0 ]
      then
         collision=1
         core=1
         deformation=1
         util=1
         view=1
		 network=1
		 collaboration=1
         if [ $action = "clean" ]
         then
            assess=1
            haptics=1
            gloves=1
            optical_trackers=1
			magnetic_trackers=1
         fi
      fi

      while [ ! -z $1 ]; do

            case $1 in
            "assess") assess=1
            ;;

            "collision") collision=1
            ;;

            "core") core=1
            ;;

            "deformation") deformation=1
            ;;

            "haptics") haptics=1
            ;;
            
            "optical_trackers") optical_trackers=1
            ;;
            
            "gloves") gloves=1
            ;;
		
			"magnetic_trackers") magnetic_trackers=1
            ;;

            "utils") util=1
            ;;

            "view") view=1
            ;;

			"network") network=1
            ;;

			"collaboration") collaboration=1
            ;;
            
            "all") 
                  assess=1
                  collision=1
                  core=1
                  deformation=1
                  haptics=1
                  optical_trackers=1
				  magnetic_trackers=1
				  gloves=1
                  util=1
                  view=1
				  network=1
				  collaboration=1
                  ;;

            *)
               echo "${vermelho}Parâmetro $1 inválido, descartando opção....${normal}"
            ;;
            esac
            shift      # Retira parâmetro da lista de parâmetros passada pelo usuário
      done

      case $action in
         "install") installLibrary ;;

         "uninstall") uninstallLibrary ;;

         "clean") cleandata ;;

         "help") menu ;;

         *) 
            echo "${vermelho}Error: Opção inválida! $action não é um comando válido para o gerenciamento dos pacotes do Cybermed${normal}"
            echo
            echo
            menu
            echo
            echo 
            ;;
      esac


else
   echo "${vermelho}Error: Nenhuma ação foi passada para o gerenciador${normal}"
   echo
   echo
   menu
   echo
   echo
fi
