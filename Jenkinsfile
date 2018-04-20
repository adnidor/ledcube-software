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
            archiveArtefacts artifacts: 'a.out'
        }
    }
}
