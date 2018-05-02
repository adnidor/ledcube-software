#!/bin/env groovy
pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh './build.sh'
            }
        }
        stage('Test') {
            steps {
                sh './tests'
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: 'ledcube.bin'
        }
    }
}
