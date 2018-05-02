#!/bin/env groovy
pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh './build.sh'
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: 'ledcube.bin'
        }
    }
}
