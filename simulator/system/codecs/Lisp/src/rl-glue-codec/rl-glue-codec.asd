
;;; Copyright 2008 Gabor Balazs
;;; Licensed under the Apache License, Version 2.0 (the "License");
;;; you may not use this file except in compliance with the License.
;;; You may obtain a copy of the License at
;;;
;;;     http://www.apache.org/licenses/LICENSE-2.0
;;;
;;; Unless required by applicable law or agreed to in writing, software
;;; distributed under the License is distributed on an "AS IS" BASIS,
;;; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;;; See the License for the specific language governing permissions and
;;; limitations under the License.
;;;
;;; $Revision: 746 $
;;; $Date: 2009-02-13 04:33:11 -0600 (Fri, 13 Feb 2009) $

(in-package #:cl-user)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defpackage #:org.rl-community.rl-glue-codec-asdf
  (:use #:asdf #:common-lisp))

(in-package #:org.rl-community.rl-glue-codec-asdf)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defsystem rl-glue-codec
  :name "RL-Glue Common Lisp Codec"
  :licence "Apache v2"
  :author "Gabor Balazs <gabalz@rl-community.org>"
  :maintainer "Gabor Balazs <gabalz@rl-community.org>"
  :description "Software protocol for connecting reinforcement 
learning agents, environments and experiments."
  :serial t
  :components
  ((:file "rl-package")
   (:file "rl-version")
   (:file "rl-buffer")
   (:file "rl-common")
   (:file "rl-network")
   (:module agent
            :serial t
            :components
            ((:file "rl-client-agent")))
   (:module environment
            :serial t
            :components
            ((:file "rl-client-environment")))
   (:module experiment
            :serial t
            :components
            ((:file "rl-client-experiment"))))
  :depends-on ("usocket"))

