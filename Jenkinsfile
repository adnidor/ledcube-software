pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                avr-gcc cubelib.c main.c
            }
        }
    }
}
