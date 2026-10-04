#!/bin/sh

#SBATCH -J "mnxb11-hplank-hw3"
#SBATCH --output=%x_%j.out         
#SBATCH --error=%x_%j.err

#SBATCH --time=00:10:00
#SBATCH -A hep2023-1-6
#SBATCH --mem 32G
#SBATCH --nodes 1

#SBATCH --mail-type=END,FAIL,BEGIN        
#SBATCH --mail-user=herman@plank.se

# Launch the calculatePI.sh application script using the container script
run_in_container_calculatePI.sh
