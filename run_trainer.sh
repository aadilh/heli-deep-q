echo "Training for Task #"$1;
echo "Number of Episodes:"$2
cd simulator/trainers/consoleTrainerJavaHelicopter/

sed -i.bak "s/whichTrainingMDP = [0-9]/whichTrainingMDP = $1/" src/consoleTrainer.java
sed -i.bak "s/episodeCount=0/episodeCount=$2/" src/consoleTrainer.java

make
bash run.bash
sed -i.bak "s/episodeCount=$2/episodeCount=0/" src/consoleTrainer.java
rm src/consoleTrainer.java.bak
