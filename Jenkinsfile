#!/bin/env groovy
pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh avr-gcc cubelib.c main.c
            }
        }
    }
}
