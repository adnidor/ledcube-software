#!/bin/env groovy
pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh 'avr-gcc -mmcu=atmega8 cubelib.c main.c'
            }
        }
    }
}
